export module fbc.CombatTurn;

import fbc.FUtil;
import fbc.IDrawable;
import fbc.TurnObject;
import std;

namespace fbc {
	export class CombatTurn {
	public:
		CombatTurn(TurnObject& source, int actionValue): source(source), actionValue(actionValue) {}

		bool isDone = false;
		func<bool(CombatTurn&)> onStart;
		int actionValue;
		TurnObject& source;

		bool operator<(const CombatTurn& other) const { return actionValue < other.actionValue; }
		bool operator>(const CombatTurn& other) const { return actionValue > other.actionValue; }

		inline IDrawable& getPortrait() { return source.getImagePortrait(); }

		void end();
		bool start();
	};

	bool CombatTurn::start()
	{
		if (onStart) {
			isDone = onStart(*this);
		}
		else {
			isDone = source.onTurnBegin();
		}
		// TODO hooks
		return isDone;
	}

	void CombatTurn::end()
	{
		source.onTurnEnd();
		// TODO hooks
	}
}