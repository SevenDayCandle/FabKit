export module fbc.CombatTurn;

import fbc.FieldObject;
import fbc.FUtil;
import std;

export namespace fbc {
	export class CombatTurn {
	public:
		CombatTurn(FieldObject& source, int actionValue): source(source), actionValue(actionValue) {}

		FieldObject& source;
		int actionValue;

		void start();
	};
}