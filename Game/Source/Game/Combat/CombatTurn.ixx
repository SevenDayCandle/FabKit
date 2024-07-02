export module fbc.CombatTurn;

import fbc.FieldObject;
import fbc.FUtil;
import fbc.UIBase;
import std;

namespace fbc {
	export class CombatTurn {
	public:
		CombatTurn(FieldObject& source, int actionValue): source(source), actionValue(actionValue) {}

		bool isDone = false;
		FieldObject& source;
		int actionValue;
		UIBase* uiElement;

		bool operator<(const CombatTurn& other) const { return actionValue < other.actionValue; }
		bool operator>(const CombatTurn& other) const { return actionValue > other.actionValue; }

		void end();
		void start();
	};

	void CombatTurn::end()
	{
		source.onTurnEnd();
		// TODO hooks
	}

	void CombatTurn::start()
	{
		isDone = source.onTurnBegin();
		// TODO hooks
	}
}