export module fbc.uiLabel;

import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.textInfo;
import fbc.uiTooltip;
import fbc.uiTipHoverable;

export namespace fbc {
	export class UILabel : public UITipHoverable, public TextInfo {
	public:
		UILabel(fbc::Hitbox* hb, FFont& f) : UITipHoverable(hb), TextInfo(f) {}
		UILabel(fbc::Hitbox* hb, FFont& f, const str& text) : UITipHoverable(hb), TextInfo(f, text) {}
		~UILabel() override {}

		virtual void renderImpl() override;
	};

	void UILabel::renderImpl() {
		TextInfo::drawText(hb->x, hb->y);
	}
}