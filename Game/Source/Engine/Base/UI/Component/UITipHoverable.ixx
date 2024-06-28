export module fbc.UITipHoverable;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.Tooltip;
import fbc.UIBase;

namespace fbc {
	export class UITipHoverable : public UIBase {
	public:
		Tooltip* tooltip;

		UITipHoverable(Hitbox* hb) : UIBase(hb), tooltip(nullptr) {}
		~UITipHoverable() override {}

		virtual void refreshDimensions() override;
		virtual void updateImpl() override;

		inline UITipHoverable& setOwnedTip(strv text) { return setOwnedTip(new Tooltip(text)); }
		inline virtual UITipHoverable& setTooltip(Tooltip* tooltip) { return this->tooltip = tooltip, *this; } // Assigns a non-owned tooltip to this object

		UITipHoverable& setOwnedTip(Tooltip* tooltip);
	private:
		uptr<Tooltip> ownedTip;
	};

	void UITipHoverable::refreshDimensions()
	{
		UIBase::refreshDimensions();
		if (tooltip) {
			tooltip->refreshCache();
		}
	}

	void UITipHoverable::updateImpl()
	{
		UIBase::updateImpl();
		if (hb->isHovered() && tooltip) {
			tooltip->queue();
		}
	}

	// Assigns an owned tooltip to this object (i.e. a tooltip that gets destroyed when this object is destroyed)
	UITipHoverable& UITipHoverable::setOwnedTip(Tooltip* tooltip)
	{
		ownedTip = uptr<Tooltip>(tooltip);
		this->tooltip = ownedTip.get();
		return *this;
	}
}