export module fbc.FieldObject;

import fbc.FUtil;
import fbc.AttributeObject;
import sdl;
import std;

export namespace fbc {
	export class FieldObject {
	public:
		virtual ~FieldObject() {}

		vec<uptr<AttributeObject>> statuses;

		virtual void act() = 0;
	};
}