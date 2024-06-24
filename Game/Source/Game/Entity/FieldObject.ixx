export module fbc.FieldObject;

import fbc.FUtil;
import fbc.FieldObjectData;
import fbc.GameObject;
import fbc.AttributeObject;
import sdl;
import std;

export namespace fbc {
	export template <c_ext<FieldObjectData> T = FieldObjectData> class FieldObject : GameObject<T> {
	public:
		FieldObject(T& data) : data(data) {}
		virtual ~FieldObject() {}

		const T& data;
		vec<uptr<AttributeObject<>>> statuses;

		virtual void act() = 0;
	};
}