export module fbc.CombatInstance;

import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.FieldObject;
import fbc.FieldObjectData;
import fbc.FUtil;
import fbc.IActionable;
import std;

export namespace fbc {
	export class CombatInstance {
	public:
		CombatInstance(int rowSize): rowSize(rowSize) {}

		void initialize();
	private:
		int rowSize = 1;
		vec<CombatSquare> field;
		vec<CombatTurn> turns;
		vec<IActionable> actionQueue;
		vec<uptr<FieldObject<>>> creatures;
	};
}