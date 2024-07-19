export module fbc.GameRun;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.GameRNG;
import fbc.RunEncounter;
import fbc.RunRoom;
import fbc.RunZone;
import fbc.SavedCreatureEntry;
import std;

namespace fbc {
	export class GameRun {
	public:
		GameRun(int seed): seed(seed) {
			initialize();
		}

		GameRNG rngCard;
		GameRNG rngEncounter;
		GameRNG rngMap;
		GameRNG rngReward;
		int faction = 0;
		vec<SavedCreatureEntry> creatures;

		inline CombatInstance* getCombatInstance() const { return combatInstance.get(); }
		inline RunRoom* getCurrentRoom() const { return currentRoom; }
		inline RunZone* getCurrentZone() const { return currentZone; }
		inline unsigned int getSeed() const { return seed; }

		RunRoom* getRoomAt(int col, int row);
		void initialize();
		void startCombat();
		void startCombat(RunEncounter* encounter);
		void startRoom(int col, int row, RunRoom* room);
		void startZone(RunZone* zone);
	private:
		int posCol;
		int posRow;
		int roomCols;
		unsigned int seed;
		RunRoom* currentRoom;
		RunZone* currentZone;
		uptr<CombatInstance> combatInstance;
		vec<RunRoom> rooms;
	};

	export uptr<GameRun> currentRun;
}