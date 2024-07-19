module;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.RunEncounter;
import fbc.RunRoom;
import sdl;
import std;

module fbc.GameRun;

namespace fbc {

	RunRoom* GameRun::getRoomAt(int col, int row)
	{
		int targetSquare = col + roomCols * row;
		return (targetSquare < rooms.size() && targetSquare >= 0 ? &rooms[targetSquare] : nullptr);
	}

	void GameRun::initialize()
	{
		// TODO
		std::mt19937 base = std::mt19937(std::random_device{}());
		base.seed(seed);
		rngCard = GameRNG(base());
		rngEncounter = GameRNG(base());
		rngMap = GameRNG(base());
		rngReward = GameRNG(base());
	}

	void GameRun::startCombat()
	{
		RunEncounter* encounter = nullptr;
		RunRoom* currentRoom = getCurrentRoom();
		if (currentRoom && currentZone) {
			encounter = currentRoom->getEncounter(*currentZone, rngEncounter);
		}
		startCombat(encounter);
	}

	// Initialize combat instance from current room
	void GameRun::startCombat(RunEncounter* encounter)
	{
		if (encounter) {
			combatInstance = make_unique<CombatInstance>();
			combatInstance->initialize(*encounter, creatures, faction);
			// TODO open combat screen (or overlay)
		}
		sdl::logInfo("Tried to start combat with no encounter.");
	}

	// Save coordinates of the current room and start it
	void GameRun::startRoom(int col, int row, RunRoom* room)
	{
		this->posCol = col;
		this->posRow = row;
		room->onEnter();
	}

	// TODO upon entering a new zone, regenerate the map
	/*
	 * Zone generation follows the following rules:
	 * 1. Adjacent rooms on the same column cannot share the same room type
	 * 2. Adjacent rooms on the same row cannot share the same room type if the room type does not allow for it
	 */
	void GameRun::startZone(RunZone* zone)
	{
		this->currentZone = zone;
		rooms.clear();

		this->roomCols = zone->data.sizeCols;

		// Weighted list of types
		vec<RunRoom::RoomType*> types = RunRoom::RoomType::allSorted();
		vec<int> weights;
		weights.reserve(types.size());
		int total = 0;
		// TODO override rate with zone's specific rate for this room type if it exists
		for (RunRoom::RoomType* type : types) {
			total += type->rate;
			weights.push_back(total);
		}

		// TODO implement room checks
		for (int i = 0; i < this->roomCols; ++i) {
			for (int j = 0; j < zone->data.sizeRows; ++j) {
				int roll = rngMap.random(0, total);
				auto it = std::ranges::upper_bound(weights, roll);
				int index = std::distance(weights.begin(), it);
				RunRoom::RoomType* type = types[index];

				// TODO Check for consecutive type with previous row
				if (j > 0) {
					int pos = i + roomCols * (j - 1);
					if (&rooms[pos].type == type) {
						
					}
				}

				rooms.push_back(RunRoom(*type));
			}
		}

	}
}