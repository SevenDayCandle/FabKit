module;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.RunEncounter;
import fbc.RunRoom;
import fbc.RunZone;
import sdl;
import std;

module fbc.GameRun;

namespace fbc {

	RunRoom* GameRun::getRoomAt(int col, int row)
	{
		int targetSquare = col + currentZone->data.sizeCols * row;
		return (targetSquare < rooms.size() && targetSquare >= 0 ? &rooms[targetSquare] : nullptr);
	}

	// TODO Get a random zone that is valid for the current number of zones ran through and that has not been encountered yet
	RunZone* GameRun::getValidZone()
	{
		vec<RunZone*> zones = RunZone::findAllAsList([this](RunZone* zone) {return !futil::has(this->encounteredZones, zone->id); });
		if (zones.size() > 0) {
			int index = rngMap.random(0, zones.size() - 1);
			return zones[index];
		}
		return nullptr;
	}

	// Generate a save object to be saved to a file
	GameRun::SaveData GameRun::generateSave()
	{
		SaveData data;
		data.seed = seed;
		// We store the map rng used when generating the map and not the rng after generating the map, so that we can regenerate the map in its exact form when reloading the run without actually storing any room data
		data.rngMap = lastRngMap;
		data.rngCard = rngCard.getCounter();
		data.rngEncounter = rngEncounter.getCounter();
		data.rngReward = rngReward.getCounter();
		data.posCol = posCol;
		data.posRow = posRow;
		data.creatures = creatures;
		data.encounteredZones = encounteredZones;
		data.faction = faction;
		if (currentZone) {
			data.currentZone = currentZone->toPair();
		}
		return data;
	}

	void GameRun::initialize()
	{
		// TODO initialize more stuff
		std::mt19937 base = std::mt19937(std::random_device{}());
		base.seed(seed);
		rngCard = GameRNG(base());
		rngEncounter = GameRNG(base());
		rngMap = GameRNG(base());
		rngReward = GameRNG(base());
	}

	void GameRun::loadFromSave(SaveData& save)
	{
		rngCard.addCounter(save.rngCard);
		rngEncounter.addCounter(save.rngEncounter);
		rngMap.addCounter(save.rngMap);
		rngReward.addCounter(save.rngReward);

		creatures = save.creatures;
		encounteredZones = save.encounteredZones;
		faction = save.faction;

		RunZone* zone = RunZone::get(save.currentZone);
		if (!zone) {
			zone = getValidZone();
			if (!zone) {
				sdl::logError("No zones available. Clearing encountered zones.");
				encounteredZones.clear();
				zone = getValidZone();
			}
		}
		if (zone) {
			startZone(zone);
		}
		else {
			throw std::runtime_error("No zones available for run");
		}

		posCol = save.posCol;
		posRow = save.posRow;
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
		else {
			sdl::logInfo("Tried to start combat with no encounter.");
		}
	}

	// Save coordinates of the current room and start it
	void GameRun::startRoom(RunRoom* room)
	{
		this->posCol = room->col;
		this->posRow = room->row;
		this->currentRoom = room;
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

		// We store the map rng used when generating the map and not the rng after generating the map, so that we can regenerate the map in its exact form when reloading the run without actually storing any room data
		this->lastRngMap = this->rngMap.getCounter();

		// Weighted list of types, sorted by rate. Only types that have a weight can spawn
		vec<RunRoom::RoomType*> types = RunRoom::RoomType::findAllAsList([](RunRoom::RoomType* type) { return type->rate > 0; });
		std::ranges::sort(types, [](RunRoom::RoomType* a, RunRoom::RoomType* b) {return b->rate - a->rate; });

		vec<int> weights;
		weights.reserve(types.size());
		int total = 0;
		// TODO override rate with zone's specific rate for this room type if it exists
		for (RunRoom::RoomType* type : types) {
			total += type->rate;
			weights.push_back(total);
		}

		// TODO implement room checks
		for (int i = 0; i < zone->data.sizeRows; ++i) {
			for (int j = 0; j < zone->data.sizeCols; ++j) {
				int roll = rngMap.random(0, total);
				auto it = std::ranges::lower_bound(weights, roll);
				int index = std::distance(weights.begin(), it);
				RunRoom::RoomType* type = types[index];

				// Check for consecutive type with previous row
				if (i > 0) {
					int pos = j + zone->data.sizeCols * (i - 1);
					if (&rooms[pos].type == type && !type->allowRepeat) {
						if (index > 0) {
							index -= 1;
						}
						else {
							index += 1;
						}
						type = types[index];
					}
				}
				// TODO Check for consecutive type with previous row and current column

				rooms.push_back(RunRoom(*type, j, i));
			}
		}

		// Set starting position
		posCol = 0;
		posRow = 0;

	}

	/* STATICS */
	void GameRun::loadRun(GameRun::SaveData& save) {
		current = make_unique<GameRun>(save);
	}

	void GameRun::startRun(int seed)
	{
		current = make_unique<GameRun>(seed);
		RunZone* zone = current->getValidZone();
		if (zone) {
			current->startZone(zone);
		}
		else {
			throw std::runtime_error("No zones available for run");
		}
	}
}