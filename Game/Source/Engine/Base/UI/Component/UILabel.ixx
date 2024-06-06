export module fbc.UILabel;

import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.TextInfo;
import fbc.UITooltip;
import fbc.UITipHoverable;

export namespace fbc {
	export class UILabel : public UITipHoverable, public TextInfo {
	public:
		UILabel(fbc::Hitbox* hb, FFont& f) : UITipHoverable(hb), TextInfo(f) {}
		UILabel(fbc::Hitbox* hb, FFont& f, const str& text) : UITipHoverable(hb), TextInfo(f, text) {}
		~UILabel() override {}

		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
	};

	void UILabel::refreshDimensions()
	{
		UITipHoverable::refreshDimensions();
		updateCache();
	}

	void UILabel::renderImpl() {
		TextInfo::drawText(hb->x, hb->y);
	}
}