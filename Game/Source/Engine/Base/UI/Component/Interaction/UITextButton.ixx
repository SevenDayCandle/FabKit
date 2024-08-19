export module fbc.UITextButton;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextDrawable;
import fbc.UIButton;

namespace fbc {
	export class UITextButton : public UIButton, public TextDrawable {
	public:
		UITextButton(FWindow& window, Hitbox* hb, IDrawable& image, FFont& f, strv text = "") : UIButton(window, hb, image), TextDrawable(f, text) {
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
		TextDrawable::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::refreshDimensions()
	{
		UIButton::refreshDimensions();
		refreshCache();
		TextDrawable::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIButton::renderImpl(rp);
		TextDrawable::drawText(rp, hb->x, hb->y, win.getW(), win.getH());
	}
}
