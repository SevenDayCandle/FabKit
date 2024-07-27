module;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.Creature;
import fbc.CreatureData;
import fbc.EncounterCreatureEntry;
import fbc.FieldObject;
import fbc.GameRun;
import fbc.FUtil;
import fbc.IActionable;
import fbc.RunEncounter;
import fbc.SavedCreatureEntry;
import sdl;
import std;

module fbc.CombatInstance;

namespace fbc {

	// Sets up a combat instance based on the given data
	void CombatInstance::initialize(RunEncounter& encounter, vec<SavedCreatureEntry>& runCreatures, int playerFaction)
	{
		// Generates squares based on the given dimensions
		this->fieldColumns = encounter.data.fieldCols;
		this->fieldRows = encounter.data.fieldRows;
		this->roundTime = roundTime;
		squares.clear();
		for (int i = 0; i < fieldColumns; i++) {
			for (int j = 0; j < fieldRows; j++) {
				squares.emplace_back(i, j);
			}
		}
		distances.resize(squares.size(), -1);

		// Creates field members based on the room parameters
		// TODO handle other fieldobject types besides creature
		int squarePos;
		for (EncounterCreatureEntry& entry : encounter.data.creatures) {
			CreatureData* data = CreatureData::get(entry.id);
			if (data) {
				Creature::Behavior* behavior = Creature::Behavior::get(data->data.behavior);
				squarePos = getSquareIndexAllowRandom(entry.posCol, entry.posRow);

				// If square is occupied, find an unoccupied one
				CombatSquare* square = squarePos < squares.size() ? &squares[squarePos] : nullptr;
				while (squarePos < squares.size() - 1 && square->getOccupant() != nullptr) {
					squarePos += 1;
					square = &squares[squarePos];
				}

				if (square) {
					uptr<Creature> pt = make_unique<Creature>(*data, behavior, entry.faction, entry.upgrades);
					Creature& creature = *pt;
					occupants.push_back(move(pt));
					square->setOccupant(&creature);
					creature.initialize(data->data.cards, data->data.passives);
					sdl::logInfo("Added creature %s on combat grid to square %d", entry.id.data(), squarePos);
				}
				else {
					sdl::logInfo("Failed to allocate creature %s on combat grid", entry.id.data());
				}
			}
		}

		// Places player characters on the field based on specified available spots in the room. If available spots are not enough, just stack horizontally (starting from the map center if there were no spots period)
		int index = 0;
		if (encounter.data.startPos.size() > index) {
			squarePos = getSquareIndexAllowRandom(encounter.data.startPos[index].first, encounter.data.startPos[index].second);
		}
		else {
			squarePos = getSquareIndex(encounter.data.fieldCols / 2, encounter.data.fieldRows / 2);
		}

		for (SavedCreatureEntry& entry : runCreatures) {
			// Do not spawn dead creatures
			if (entry.health > 0) {
				CreatureData* data = CreatureData::get(entry.content, entry.id);
				if (data) {
					Creature::Behavior* behavior = Creature::Behavior::get(entry.behaviorId);

					// If square is occupied, find an unoccupied one
					CombatSquare* square = squarePos < squares.size() ? &squares[squarePos] : nullptr;
					while (squarePos < squares.size() - 1 && square->getOccupant() != nullptr) {
						squarePos += 1;
						square = &squares[squarePos];
					}

					if (square) {
						uptr<Creature> pt = make_unique<Creature>(*data, behavior, playerFaction, entry.upgrades, entry.health);
						Creature& creature = *pt;
						occupants.push_back(move(pt));
						square->setOccupant(&creature);
						creature.initialize(entry.cards, entry.passives);
						sdl::logInfo("Added creature %s on combat grid to square %d", entry.id.data(), squarePos);
					}
					else {
						sdl::logInfo("Failed to allocate creature %s on combat grid", entry.id.data());
					}

					++index;
					if (encounter.data.startPos.size() > index) {
						squarePos = getSquareIndexAllowRandom(encounter.data.startPos[index].first, encounter.data.startPos[index].second);
					}
					else {
						squarePos += 1;
					}
				}
			}
		}

		// TODO Setup subscribers

		// TODO Setup initial turns

		// TODO Start of combat hooks for all field members
	}

	// Queue an action to be executed
	void CombatInstance::queueAction(uptr<IActionable>&& action)
	{
		actionQueue.push_back(move(action));
		// TODO vfx & hooks
	}

	// Marks the current turn as being completed, so that it can be pushed out after actions are done
	void CombatInstance::queueCompleteTurn()
	{
		if (currentTurn) {
			currentTurn->isDone = true;
		}
	}

	// Queue a turn to be executed. Turn queue is always sorted by ascending action order. ActionValue is relative to the total action time that has already elapsed
	void CombatInstance::queueTurn(FieldObject& source, int actionValue)
	{
		const CombatTurn& turn = *turns.emplace(source, totalActionTime + actionValue);
		// TODO vfx & hooks
	}

	// Generate a distance map from the source to all other squares
	void CombatInstance::fillDistances(CombatSquare* source)
	{
		if (source != distanceSource) {
			std::ranges::fill(distances, -1);
			distanceSource = source;
			fillDistancesImpl(source->col, source->row, 0);
		}
	}

	// Calculate the distance from this particular square to the source
	void CombatInstance::fillDistancesImpl(int col, int row, int dist)
	{
		// TODO check for square passability
		int* sq = getDistanceSquare(col, row);
		if (sq && *sq > -1) {
			*sq = dist;
			int next = dist + 1;
			fillDistancesImpl(col - 1, row - 1, next);
			fillDistancesImpl(col - 1, row + 1, next);
			fillDistancesImpl(col + 1, row - 1, next);
			fillDistancesImpl(col + 1, row + 1, next);
		}
	}

	// Change the action order for all turns corresponding with the target
	bool CombatInstance::modifyTurnOrder(const FieldObject& target, int diff)
	{
		for (auto it = turns.begin(); it != turns.end(); ) {
			if (&(it->source) == &target) {
				CombatTurn modifiedTurn = move(*it);
				modifiedTurn.actionValue += diff;
				it = turns.erase(it);
				turns.insert(move(modifiedTurn));
			}
			else {
				++it;
			}
		}
		return false;
	}

	// Drops the current turn and starts the next turn in the queue. Returns true if there are no more turns left
	bool CombatInstance::nextTurn()
	{
		if (!turns.empty()) {
			auto it = turns.begin();
			CombatTurn* turn = const_cast<CombatTurn*>(&*it);
			turn->end();
			totalActionTime = turn->actionValue;
			turns.erase(it);
			// TODO round end logic
		}
		currentTurn = nullptr;
		if (!turns.empty()) {
			currentTurn = const_cast<CombatTurn*>(&*turns.begin());
			currentTurn->start();
			return false;
		}
		return true;
		// TODO vfx & hooks
	}

	/* Runs a loop of the combat
	 * Returns true if the combat instance should stop running
	 */
	bool CombatInstance::update()
	{
		// Run current action
		if (currentAction) {
			if (currentAction->isDone()) {
				currentAction = nullptr;
				actionQueue.pop_front();
			}
			return false;
		}
		// Otherwise poll actions if any are present
		else if (!actionQueue.empty()) {
			currentAction = actionQueue.front().get();
			currentAction->start();
			return false;
		}
		// Otherwise run current turn
		else if (currentTurn && !currentTurn->isDone) {
			return false;
		}
		// Otherwise poll the next turn if it is present
		return nextTurn();
	}

	// Get the distance to the col/row position from the source. Return null if invalid
	int* CombatInstance::getDistanceSquare(int col, int row)
	{
		int targetSquare = getSquareIndex(col, row);
		return (targetSquare < distances.size() && targetSquare >= 0 ? &distances[targetSquare] : nullptr);
	}

	// Wrapper around getSquareIndex that treats negative values as random
	int CombatInstance::getSquareIndexAllowRandom(int col, int row)
	{
		int squareCol = col < 0 ? GameRun::current->rngEncounter.random(0, fieldColumns - 1) : col;
		int squareRow = row < 0 ? GameRun::current->rngEncounter.random(0, fieldRows - 1) : row;
		return getSquareIndex(squareCol, squareRow);
	}

	// Get the square at the col/row position
	CombatSquare* CombatInstance::getSquare(int col, int row)
	{
		int targetSquare = getSquareIndex(col, row);
		return (targetSquare < squares.size() && targetSquare >= 0 ? &squares[targetSquare] : nullptr);
	}

	// Get the distance from the distance source to the given square. Return -1 if unreachable
	int CombatInstance::getDistanceTo(CombatSquare* square)
	{
		int* distance = getDistanceSquare(square->col, square->row);
		return distance != nullptr ? *distance : -1;
	}
}