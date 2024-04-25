export module fbc.uiTipHoverable;

import fbc.futil;
import fbc.hitbox;
import fbc.uiTooltip;
import fbc.uiHoverable;

export namespace fbc {
	export class UITipHoverable : public UIHoverable {
	public:
		UITooltip* tooltip;

		UITipHoverable(Hitbox* hb) : UIHoverable(hb), tooltip(nullptr) {}
		~UITipHoverable() override {}

		virtual void updateImpl() override;

		inline virtual UITipHoverable& setTooltip(UITooltip* tooltip) {
			this->tooltip = tooltip;
			return *this;
		}
	};

	void UITipHoverable::updateImpl()
	{
		UIHoverable::updateImpl();
		if (hb->isHovered()) {
			// TODO queue tooltip
		}
	}
}