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
		TurnObject& source;
		int actionValue;

		bool operator<(const CombatTurn& other) const { return actionValue < other.actionValue; }
		bool operator>(const CombatTurn& other) const { return actionValue > other.actionValue; }

		inline IDrawable& getPortrait() { return source.getImagePortrait(); }

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