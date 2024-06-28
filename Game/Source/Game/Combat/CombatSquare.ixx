export module fbc.CombatSquare;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import std;

namespace fbc {
	export class CombatSquare : FieldObject {
	public:
		CombatSquare(int pos): pos(pos) {}

		const int pos;
		FieldObject* occuptant;
	};
}