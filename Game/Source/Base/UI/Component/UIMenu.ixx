export module fbc.UIMenu;

import fbc.hitbox;
import fbc.uiHoverable;
import fbc.futil;

export namespace fbc {
	export class UIMenu : public UIHoverable {
	public:
		UIMenu(Hitbox* hb): UIHoverable(hb) {}
		virtual ~UIMenu() {}
	};
}