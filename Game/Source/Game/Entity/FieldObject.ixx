export module fbc.FieldObject;

import fbc.AttributeObject;
import fbc.FUtil;
import fbc.IDrawable;
import std;

namespace fbc {
	export class FieldObject {
	public:
		FieldObject() {}
		FieldObject(FieldObject&& other) = default;
		virtual ~FieldObject() = default;

		vec<uptr<AttributeObject>> statuses;
	};
}