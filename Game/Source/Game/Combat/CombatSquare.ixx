export module fbc.CombatSquare;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import std;

export namespace fbc {
	export class CombatSquare {
	public:
		CombatSquare() {}

		FieldObject* occuptant;
		vec<uptr<AttributeObject>> attributes;
	};
}