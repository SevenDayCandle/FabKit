export module fbc.AttributeObject;

import fbc.FUtil;
import sdl;
import std;

export namespace fbc {
	export class AttributeObject {
	public:
		virtual ~AttributeObject() {}

		virtual void act() = 0;
	};
}