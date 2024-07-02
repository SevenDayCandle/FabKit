export module fbc.FieldObject;

import fbc.FUtil;
import fbc.AttributeObject;
import std;

namespace fbc {
	export class FieldObject {
	public:
		FieldObject() {}
		FieldObject(FieldObject&& other) = default;
		virtual ~FieldObject() = default;

		vec<uptr<AttributeObject>> statuses;

		inline virtual void onTurnEnd() {}

		virtual bool onTurnBegin() = 0;
	};
}