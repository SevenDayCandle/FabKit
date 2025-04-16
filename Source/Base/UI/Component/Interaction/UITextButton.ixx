export module fab.UITextButton;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.TextDrawable;
import fab.UIButton;
import sdl.SDLBase;
import sdl.SDLBatchRenderPass;

namespace fab {
	export class UITextButton : public UIButton {
	public:
		UITextButton(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image, FFont& f, strv text = "") : UIButton(window, move(hb), image), text(f, text) {
			UITextButton::onSizeUpdated();
		}
		UITextButton(FWindow& window, uptr<Hitbox>&& hb, strv text) : UITextButton(window, move(hb), window.props.defaultButton(), window.props.fontRegular(), text) {}
		~UITextButton() override {}

		inline UITextButton& setColor(sdl::Color color) { return text.setColor(color), * this; }
		inline UITextButton& setColorOutline(sdl::Color colorOutline) { return text.setColorOutline(colorOutline), * this; }
		inline UITextButton& setFont(const FFont& font) { return text.setFont(font), * this; }
		inline UITextButton& setText(strv t) { return text.setText(t), * this; }

		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	protected:
		TextDrawable text;
	};

	void UITextButton::refreshDimensions()
	{
		UIButton::refreshDimensions();
		text.setWidth(hb->w);
	}

	void UITextButton::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIButton::renderImpl(rp);
		text.drawCenteredFull(rp, hb->cX(), hb->cY(), win.getW(), win.getH());
	}
}
