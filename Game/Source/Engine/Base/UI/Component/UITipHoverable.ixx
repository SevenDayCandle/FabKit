export module fbc.uiTipHoverable;

import fbc.futil;
import fbc.hitbox;
import fbc.uiTooltip;
import fbc.uiBase;

export namespace fbc {
	export class UITipHoverable : public UIBase {
	public:
		UITooltip* tooltip;

		UITipHoverable(Hitbox* hb) : UIBase(hb), tooltip(nullptr) {}
		~UITipHoverable() override {}

		virtual void updateImpl() override;

		inline virtual UITipHoverable& setTooltip(UITooltip* tooltip) {
			this->tooltip = tooltip;
			return *this;
		}
	};

	void UITipHoverable::updateImpl()
	{
		UIBase::updateImpl();
		if (hb->isHovered()) {
			// TODO queue tooltip
		}
	}
}