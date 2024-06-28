export module fbc.CombatInstance;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IActionable;
import std;

namespace fbc {
	export constexpr int DEFAULT_ROUND_LENGTH = 100;

	export class CombatInstance {
	public:
		CombatInstance(int columns, int rows, int roundTime = DEFAULT_ROUND_LENGTH): fieldColumns(columns), fieldRows(rows), roundTime(roundTime) {}

		inline bool hasAction() const { return currentAction != nullptr; }
		inline CombatTurn* getCurrentTurn() const { return currentTurn; }
		inline IActionable* getCurrentAction() const { return currentAction; }
		inline int getCurrentRound() const { return totalActionTime / roundTime; }
		inline int getTotalActionTime() const { return totalActionTime; }

		bool modifyTurnOrder(const FieldObject& target, int diff);
		bool nextTurn();
		bool update();
		void initialize();
		void queueAction(uptr<IActionable>&& action);
		void queueCompleteTurn();
		void queueTurn(FieldObject& source, int actionValue);
	private:
		CombatTurn* currentTurn;
		deque<uptr<IActionable>> actionQueue;
		IActionable* currentAction;
		mset<CombatTurn> turns;
		int fieldColumns = 1;
		int fieldRows = 1;
		int roundTime = DEFAULT_ROUND_LENGTH;
		int totalActionTime = 0;
		vec<CombatSquare> field;
		vec<uptr<FieldObject>> fieldObjects;
	};

	/*
	 * 1. Generates squares based on the given dimensions 
	 */
	void CombatInstance::initialize()
	{
		// Generates squares based on the given dimensions
		for (int i = 0; i < fieldColumns * fieldRows; i++) {
			field.push_back(CombatSquare(i));
		}

		// Creates field members based on the room parameters

		// Setup subscribers

		// Setup initial turns

		// Initialize all field members
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
		turns.emplace(source, totalActionTime + actionValue);
		// TODO vfx & hooks
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
}