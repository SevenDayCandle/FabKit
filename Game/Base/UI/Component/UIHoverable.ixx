export module fbc.uiHoverable;

import fbc.futil;
import fbc.hitbox;
import fbc.tooltip;
import fbc.uiBase;

export namespace fbc::cpt {
	export class UIHoverable : public UIBase {
	public:
		uptr<hitbox::Hitbox> hb;
		sptr<tooltip::Tooltip> tooltip;

		UIHoverable(hitbox::Hitbox* hb): hb(hb), tooltip(nullptr) {}
		~UIHoverable() override {}

		virtual void renderImpl() override;
		virtual void updateImpl() override;

		inline virtual UIHoverable& setTooltip(sptr<tooltip::Tooltip> tooltip) {
			this->tooltip = tooltip;
			return *this;
		}
	};


	void UIHoverable::renderImpl()
	{
		// TODO render tooltip
	}

	void UIHoverable::updateImpl()
	{
		hb->update();
		if (hb->isHovered()) {
			// TODO queue tooltip
		}
	}
}