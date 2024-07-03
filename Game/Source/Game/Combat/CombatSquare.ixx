export module fbc.CombatSquare;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.UIBase;
import std;

namespace fbc {
	export class CombatSquare : FieldObject {
	public:
		CombatSquare(int col, int row): col(col), row(row) {}

		int col;
		int row;
		UIBase* drawable;

		inline bool onTurnBegin() override { return true; }
		inline FieldObject* getOccupant() const { return occupant; }

		CombatSquare& setOccupant(FieldObject* occupant);
	private:
		FieldObject* occupant = nullptr;
	};
}