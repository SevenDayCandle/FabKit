export module fbc.uiText;

import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.textInfo;
import fbc.tooltip;
import fbc.uiHoverable;

export namespace fbc::cpt {
	export class UIText : public UIHoverable, public TextInfo {
	public:
		UIText(fbc::hitbox::Hitbox* hb, sptr<fbc::FFont> f) : UIHoverable(hb), TextInfo(f) {}
		~UIText() override {}

		virtual void renderImpl() override;
		virtual void updateImpl() override;
	};

	void UIText::renderImpl() {
		this->UIHoverable::renderImpl();
		TextInfo::drawText(hb->x, hb->y);
	}

	void UIText::updateImpl() {
		this->UIHoverable::updateImpl();
	}
}