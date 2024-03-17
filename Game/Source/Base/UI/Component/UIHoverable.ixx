export module fbc.uiHoverable;

import fbc.futil;
import fbc.hitbox;
import fbc.uiBase;

export namespace fbc {
	export class UIHoverable : public UIBase {
	public:
		uptr<Hitbox> hb;

		UIHoverable(Hitbox* hb): hb(hb) {}
		~UIHoverable() override {}

		virtual bool isHovered();
		virtual void updateImpl() override;
	};

	// Return true if this object is hovered
	bool UIHoverable::isHovered() {
		return hb->isHovered();
	}

	void UIHoverable::updateImpl() {
		hb->update();
	}
}