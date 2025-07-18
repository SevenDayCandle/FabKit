export module fab.UILabel;

import fab.FFont;
import fab.FWindow;
import fab.FUtil;
import fab.Hitbox;
import fab.TextDrawable;
import fab.Tooltip;
import fab.UIBase;
import sdl.SDLBase;
import fab.BatchRenderPass;

namespace fab {
	export class UILabel : public UIBase {
	public:
		UILabel(FWindow& window, uptr<Hitbox>&& hb, FFont& f, strv text = "") : UIBase(window, move(hb)), text(f, text, hb->w) {}
		~UILabel() override {}

		inline UILabel& setColor(sdl::Color color) { return text.setColor(color), *this; }
		inline UILabel& setColorOutline(sdl::Color colorOutline) { return text.setColorOutline(colorOutline), *this; }
		inline UILabel& setFont(FFont& font) { return text.setFont(font), *this; }
		inline UILabel& setText(strv t) { return text.setText(t), *this; }

		void refreshDimensions() override;
		void renderImpl(BatchRenderPass& rp) override;
	protected:
		TextDrawable text;
	};

	void UILabel::refreshDimensions() {
		UIBase::refreshDimensions();
		text.setWidth(hb->w);
	}

	void UILabel::renderImpl(BatchRenderPass& rp) {
		text.drawFull(rp, hb->x, hb->y);
	}
}
