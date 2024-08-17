export module fbc.UILabel;

import fbc.FFont;
import fbc.FWindow;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.TextInfo;
import fbc.Tooltip;
import fbc.UITipHoverable;

namespace fbc {
	export class UILabel : public UITipHoverable, public TextInfo {
	public:
		UILabel(FWindow& window, Hitbox* hb, FFont& f) : UITipHoverable(window, hb), TextInfo(f) {}
		UILabel(FWindow& window, Hitbox* hb, FFont& f, const str& text) : UITipHoverable(window, hb), TextInfo(f, text) {}
		~UILabel() override {}

		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void UILabel::refreshDimensions()
	{
		UITipHoverable::refreshDimensions();
		refreshCache();
	}

	void UILabel::renderImpl(sdl::SDLBatchRenderPass& rp) {
		TextInfo::drawText(rp, hb->x, hb->y, win.getW(), win.getH());
	}
}