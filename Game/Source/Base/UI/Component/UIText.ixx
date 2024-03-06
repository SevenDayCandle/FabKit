export module fbc.uiText;

import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.textInfo;
import fbc.tooltip;
import fbc.uiTipHoverable;

export namespace fbc::ui {
	export class UIText : public UITipHoverable, public ITextInfo {
	public:
		UIText(fbc::ui::Hitbox* hb, sptr<fbc::FFont> f) : UITipHoverable(hb), ITextInfo(f) {}
		~UIText() override {}

		virtual void renderImpl() override;
		virtual void updateImpl() override;
	};

	void UIText::renderImpl() {
		this->UITipHoverable::renderImpl();
		ITextInfo::drawText(hb->x, hb->y);
	}

	void UIText::updateImpl() {
		this->UITipHoverable::updateImpl();
	}
}