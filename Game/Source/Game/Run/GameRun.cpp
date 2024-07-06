module;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.RunEncounter;
import fbc.RunRoom;
import sdl;
import std;

module fbc.GameRun;

namespace fbc {

	void GameRun::initialize()
	{
		// TODO
		std::mt19937 base = std::mt19937(std::random_device{}());
		base.seed(seed);
		rngCard = GameRNG(base());
		rngEncounter = GameRNG(base());
		rngReward = GameRNG(base());
	}

	void GameRun::startCombat()
	{
		RunEncounter* encounter = nullptr;
		if (currentRoom) {
			encounter = currentRoom->getEncounter(rngEncounter);
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
}