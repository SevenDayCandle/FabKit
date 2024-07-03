export module fbc.FieldObject;

import fbc.AttributeObject;
import fbc.FUtil;
import std;

namespace fbc {
	export class CombatSquare;
	export class FieldObject {
	public:
		FieldObject() {}
		FieldObject(FieldObject&& other) = default;
		virtual ~FieldObject() = default;

		CombatSquare* currentSquare;
		vec<uptr<AttributeObject>> statuses;

		inline virtual void onTurnEnd() {}

		virtual bool onTurnBegin() = 0;
	};
}