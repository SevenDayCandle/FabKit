export module fbc.CombatInstance;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.EncounterCreatureEntry;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IActionable;
import fbc.RunEncounter;
import fbc.SavedCreatureEntry;
import std;

namespace fbc {
	export constexpr int DEFAULT_ROUND_LENGTH = 100;

	export class CombatInstance {
	public:
		CombatInstance() {}

		inline bool hasAction() const { return currentAction != nullptr; }
		inline CombatTurn* getCurrentTurn() const { return currentTurn; }
		inline IActionable* getCurrentAction() const { return currentAction; }
		inline int getCurrentRound() const { return totalActionTime / roundTime; }
		inline int getTotalActionTime() const { return totalActionTime; }

		bool modifyTurnOrder(const FieldObject& target, int diff);
		bool nextTurn();
		bool update();
		CombatSquare* getSquare(int col, int row);
		int getDistanceTo(CombatSquare* square);
		vec<CombatSquare*> findShortestPath(CombatSquare* targ);
		void fillDistances(CombatSquare* source);
		void initialize(RunEncounter& encounter, vec<SavedCreatureEntry>& runCreatures, int playerFaction);
		void queueAction(uptr<IActionable>&& action);
		void queueCompleteTurn();
		void queueTurn(FieldObject& source, int actionValue);
	private:
		CombatSquare* distanceSource;
		CombatTurn* currentTurn;
		deque<uptr<IActionable>> actionQueue;
		IActionable* currentAction;
		mset<CombatTurn> turns;
		int fieldColumns = 1;
		int fieldRows = 1;
		int roundTime = DEFAULT_ROUND_LENGTH;
		int totalActionTime = 0;
		vec<CombatSquare> squares;
		vec<int> distances;
		vec<uptr<FieldObject>> fieldObjects;

		int* getDistanceSquare(int col, int row);
		void fillDistancesImpl(int col, int row, int dist);
	};
}