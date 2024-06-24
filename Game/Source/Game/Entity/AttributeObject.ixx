export module fbc.AttributeObject;

import fbc.FUtil;
import fbc.AttributeObjectData;
import fbc.GameObject;
import sdl;
import std;

export namespace fbc {
	export template <c_ext<AttributeObjectData> T = AttributeObjectData> class AttributeObject : GameObject<T> {
	public:
		AttributeObject(T& data) : data(data) {}
		virtual ~AttributeObject() {}

		const T& data;

		virtual void act() = 0;
	};
}