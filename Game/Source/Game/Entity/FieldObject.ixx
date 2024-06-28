export module fbc.FieldObject;

import fbc.FUtil;
import fbc.AttributeObject;
import sdl;
import std;

namespace fbc {
	export class FieldObject {
	public:
		virtual ~FieldObject() {}

		vec<uptr<AttributeObject>> statuses;

		inline virtual void onEndTurn() {}

		virtual bool act() = 0;
	};
}