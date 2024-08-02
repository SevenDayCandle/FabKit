export module fbc.AttributeObject;

namespace fbc {
	export class AttributeObject {
	public:
		AttributeObject() {}
		AttributeObject(AttributeObject&& other) = default;
		virtual ~AttributeObject() = default;

		virtual void act() = 0;
	};
}