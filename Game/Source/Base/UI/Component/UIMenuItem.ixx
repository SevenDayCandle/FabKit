export module fbc.UIMenuItem;

import fbc.hitbox;
import fbc.uiHoverable;
import fbc.futil;

export namespace fbc {
	export template<typename T> class UIMenuItem : public UIHoverable {
	public:
		UIMenuItem(Hitbox* hb): UIHoverable(hb) {}
		virtual ~UIMenuItem() {}
	protected:
		T item;
	};
}