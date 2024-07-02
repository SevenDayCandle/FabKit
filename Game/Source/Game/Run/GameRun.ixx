export module fbc.GameRun;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.RunRoom;
import std;

namespace fbc {
	export class GameRun {
	public:
		GameRun() {}

		inline CombatInstance* getCombatInstance() const { return combatInstance; }
		inline RunRoom* getCurrentRoom() const { return currentRoom; }

		void initialize();
		void startCombat();
	private:
		CombatInstance* combatInstance;
		RunRoom* currentRoom;
	};

	export GameRun* currentRun;
}