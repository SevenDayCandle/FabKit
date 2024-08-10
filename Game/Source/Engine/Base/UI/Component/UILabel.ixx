export module fbc.UILabel;

import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.TextInfo;
import fbc.Tooltip;
import fbc.UITipHoverable;

namespace fbc {
	export class UILabel : public UITipHoverable, public TextInfo {
	public:
		UILabel(fbc::Hitbox* hb, FFont& f) : UITipHoverable(hb), TextInfo(f) {}
		UILabel(fbc::Hitbox* hb, FFont& f, const str& text) : UITipHoverable(hb), TextInfo(f, text) {}
		~UILabel() override {}

		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
	};

	void UILabel::refreshDimensions()
	{
		UITipHoverable::refreshDimensions();
		refreshCache();
	}

	void UILabel::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		TextInfo::drawText(hb->x, hb->y);
	}
}