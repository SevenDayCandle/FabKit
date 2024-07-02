export module fbc.AttributeObject;

import fbc.FUtil;
import std;

namespace fbc {
	export class AttributeObject {
	public:
		AttributeObject() {}
		AttributeObject(AttributeObject&& other) = default;
		virtual ~AttributeObject() = default;

		virtual void act() = 0;
	};
}