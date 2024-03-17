export module fbc.uiTipHoverable;

import fbc.futil;
import fbc.hitbox;
import fbc.tooltip;
import fbc.uiHoverable;

export namespace fbc {
	export class UITipHoverable : public UIHoverable {
	public:
		sptr<tooltip::Tooltip> tooltip;

		UITipHoverable(Hitbox* hb) : UIHoverable(hb), tooltip(nullptr) {}
		~UITipHoverable() override {}

		virtual void renderImpl() override;
		virtual void updateImpl() override;

		inline virtual UITipHoverable& setTooltip(sptr<tooltip::Tooltip> tooltip) {
			this->tooltip = tooltip;
			return *this;
		}
	};


	void UITipHoverable::renderImpl()
	{
		// TODO render tooltip
	}

	void UITipHoverable::updateImpl()
	{
		UIHoverable::updateImpl();
		if (hb->isHovered()) {
			// TODO queue tooltip
		}
	}
}