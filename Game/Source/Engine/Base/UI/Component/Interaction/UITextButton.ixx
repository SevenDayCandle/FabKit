export module fbc.UITextButton;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.UIButton;

namespace fbc {
	export class UITextButton : public UIButton, public TextInfo {
	public:
		UITextButton(FWindow& window, Hitbox* hb, IDrawable& image, FFont& f, strv text = "") : UIButton(window, hb, image), TextInfo(f, text) {
			UITextButton::onSizeUpdated();
		}
		UITextButton(FWindow& window, Hitbox* hb, strv text) : UITextButton(window, hb, cct.images.uiPanel, cct.fontRegular(), text) {}
		~UITextButton() override {}

		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void UITextButton::onSizeUpdated()
	{
		TextInfo::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::refreshDimensions()
	{
		UIButton::refreshDimensions();
		refreshCache();
		TextInfo::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIButton::renderImpl(rp);
		TextInfo::drawText(rp, hb->x, hb->y, win.getW(), win.getH());
	}
}
