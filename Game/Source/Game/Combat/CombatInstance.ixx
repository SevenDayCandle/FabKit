export module fbc.CombatInstance;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IActionable;
import std;

export namespace fbc {
	export class CombatInstance {
	public:
		CombatInstance(int columns, int rows): columns(columns), rows(rows) {}

		void queueAction(uptr<IActionable>&& action);
		void queueTurn(FieldObject& source, int actionSpeed);
		void initialize();
		bool update();
	private:
		CombatTurn* currentTurn;
		deque<uptr<IActionable>> actionQueue;
		deque<CombatTurn> turns;
		IActionable* currentAction;
		int columns = 1;
		int rows = 1;
		vec<CombatSquare> field;
		vec<uptr<FieldObject>> fieldObjects;
	};

	/*
	 * 1. Generates squares based on the given dimensions 
	 */
	void CombatInstance::initialize()
	{
		// Generates squares based on the given dimensions

		// Creates field members based on the room parameters

		// Setup subscribers

		// Setup initial turns
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
			currentAction = actionQueue.front;
			currentAction->start();
			return false;
		}
		// Otherwise run current turn
		else if (currentTurn) {
			if (currentTurn->isDone) {
				currentTurn = nullptr;
				turns.pop_front();
			}
			return false;
		}
		// Otherwise poll the next turn if it is present
		else if (!turns.empty()) {
			currentTurn = turns.front;
			currentTurn->start();
			return false;
		}
		return true;
	}
}