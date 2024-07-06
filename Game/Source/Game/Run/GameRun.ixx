export module fbc.GameRun;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.GameRNG;
import fbc.RunEncounter;
import fbc.RunRoom;
import fbc.SavedCreatureEntry;
import std;

namespace fbc {
	export class GameRun {
	public:
		GameRun(int seed): seed(seed) {
			initialize();
		}

		inline CombatInstance* getCombatInstance() const { return combatInstance.get(); }
		inline RunRoom* getCurrentRoom() const { return currentRoom.get(); }
		inline unsigned int getSeed() const { return seed; }

		GameRNG rngCard;
		GameRNG rngEncounter;
		GameRNG rngReward;
		int faction = 0;
		vec<SavedCreatureEntry> creatures;

		void initialize();
		void startCombat();
		void startCombat(RunEncounter* encounter);
	private:
		unsigned int seed;
		uptr<CombatInstance> combatInstance;
		uptr<RunRoom> currentRoom;
	};

	export uptr<GameRun> currentRun;
}