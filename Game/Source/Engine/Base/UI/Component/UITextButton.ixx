export module fbc.uiTextButton;

import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.textInfo;
import fbc.uiButton;

export namespace fbc {
	export class UITextButton : public UIButton, public TextInfo {
	public:
		UITextButton(Hitbox* hb, IDrawable& image, FFont& f) : UIButton(hb, image), TextInfo(f) {}
		UITextButton(Hitbox* hb, IDrawable& image, FFont& f, str text) : UIButton(hb, image), TextInfo(f, text) {}
		~UITextButton() override {}

		virtual void renderImpl() override;
	};

	void UITextButton::renderImpl() {
		UIButton::renderImpl();
		float textX = hb->x + (hb->w - getTextWidth()) / 2;
		float textY = hb->cY() - (getTextHeight() / 2);
		TextInfo::drawText(textX, textY);
	}
}
