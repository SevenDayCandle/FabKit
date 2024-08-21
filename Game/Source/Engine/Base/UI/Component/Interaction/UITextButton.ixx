export module fbc.UITextButton;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextDrawable;
import fbc.UIButton;
import sdl.SDLBatchRenderPass;

namespace fbc {
	export class UITextButton : public UIButton {
	public:
		UITextButton(FWindow& window, Hitbox* hb, IDrawable& image, FFont& f, strv text = "") : UIButton(window, hb, image), text(f, text) {
			UITextButton::onSizeUpdated();
		}
		UITextButton(FWindow& window, Hitbox* hb, strv text) : UITextButton(window, hb, cct.images.uiPanel, cct.fontRegular(), text) {}
		~UITextButton() override {}

		inline UITextButton& setColor(sdl::Color color) { return text.setColor(color), * this; }
		inline UITextButton& setColorOutline(sdl::Color colorOutline) { return text.setColorOutline(colorOutline), * this; }
		inline UITextButton& setFont(const FFont& font) { return text.setFont(font), * this; }
		inline UITextButton& setText(strv t) { return text.setText(t), * this; }

		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	protected:
		TextDrawable text;
	};

	void UITextButton::onSizeUpdated()
	{
		text.setPos((this->hb->w - text.getWidth()) / 2, (this->hb->h - text.getHeight()) / 2);
	}

	void UITextButton::refreshDimensions()
	{
		UIButton::refreshDimensions();
		text.setWidth(hb->w);
	}

	void UITextButton::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIButton::renderImpl(rp);
		text.draw(rp, hb->x, hb->y, win.getW(), win.getH());
	}
}
