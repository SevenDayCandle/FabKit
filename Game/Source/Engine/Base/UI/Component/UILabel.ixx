export module fbc.UILabel;

import fbc.FFont;
import fbc.FWindow;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.TextDrawable;
import fbc.Tooltip;
import fbc.UITipHoverable;
import sdl.SDLBatchRenderPass;

namespace fbc {
	export class UILabel : public UITipHoverable {
	public:
		UILabel(FWindow& window, Hitbox* hb, FFont& f, strv text = "") : UITipHoverable(window, hb), text(f, text, hb->w) {}
		~UILabel() override {}

		inline UILabel& setColor(sdl::Color color) { return text.setColor(color), * this; }
		inline UILabel& setColorOutline(sdl::Color colorOutline) { return text.setColorOutline(colorOutline), * this; }
		inline UILabel& setFont(const FFont& font) { return text.setFont(font), * this; }
		inline UILabel& setText(strv t) { return text.setText(t), * this; }

		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	protected:
		TextDrawable text;
	};

	void UILabel::refreshDimensions()
	{
		UITipHoverable::refreshDimensions();
		text.setWidth(hb->w);
	}

	void UILabel::renderImpl(sdl::SDLBatchRenderPass& rp) {
		text.draw(rp, hb->x, hb->y, win.getW(), win.getH());
	}
}