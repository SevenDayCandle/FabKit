export module fbc.uiText;

import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.textInfo;
import fbc.tooltip;
import fbc.uiTipHoverable;

export namespace fbc {
	export class UIText : public UITipHoverable, public TextInfo {
	public:
		UIText(fbc::Hitbox* hb, FFont& f) : UITipHoverable(hb), TextInfo(f) {}
		UIText(fbc::Hitbox* hb, FFont& f, const str& text) : UITipHoverable(hb), TextInfo(f, text) {}
		~UIText() override {}

		virtual void renderImpl() override;
	};

	void UIText::renderImpl() {
		UITipHoverable::renderImpl();
		TextInfo::drawText(hb->x, hb->y);
	}
}