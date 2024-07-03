module;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.Creature;
import fbc.CreatureData;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IActionable;
import std;

module fbc.CombatInstance;

namespace fbc {
	/*
 * 1. Generates squares based on the given dimensions
 */
	void CombatInstance::initialize(int columns, int rows, int roundTime, vec<CombatRunCreatureEntry>& inputFieldObjects)
	{
		// Generates squares based on the given dimensions
		this->fieldColumns = columns;
		this->fieldRows = rows;
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
		for (CombatRunCreatureEntry& entry : inputFieldObjects) {
			CreatureData* data = CreatureData::get(entry.dataId);
			if (data) {
				Creature::Behavior* behavior = Creature::Behavior::optGet(entry.behaviorId);
				if (!behavior) {
					behavior = Creature::Behavior::optGet(data->data.defaultBehavior);
				}

				CombatSquare* square = getSquare(entry.posCol, entry.posRow);

				if (behavior && square) {
					uptr<Creature> pt = make_unique<Creature>(*data, behavior, entry.faction, entry.upgrades, entry.health);
					Creature& creature = *pt;
					fieldObjects.push_back(move(pt));
					square->setOccupant(&creature);
					creature.initialize(entry.cards, entry.passives);
				}
			}
		}

		// Setup subscribers

		// Setup initial turns

		// Start of combat hooks for all field members
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

	void CombatInstance::fillDistancesImpl(int col, int row, int dist)
	{
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
		int targetSquare = col + fieldColumns * row;
		return (targetSquare < distances.size() && targetSquare >= 0 ? &distances[targetSquare] : nullptr);
	}

	// Get the square at the col/row position
	CombatSquare* CombatInstance::getSquare(int col, int row)
	{
		int targetSquare = col + fieldColumns * row;
		return (targetSquare < squares.size() && targetSquare >= 0 ? &squares[targetSquare] : nullptr);
	}
}