export module fbc.UITitledInteractable;

import fbc.CoreContent;
import fbc.CoreConfig;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.TextInfo;
import sdl;
import std;

export namespace fbc {
	export class UITitledInteractable : public UIInteractable {
	public:
		UITitledInteractable(Hitbox* hb, IDrawable& image) : UIInteractable(hb, image) {}
		UITitledInteractable(Hitbox* hb, IDrawable& image, sdl::Point origin) : UIInteractable(hb, image, origin) {}
		virtual ~UITitledInteractable() override {}

		uptr<TextInfo> label;

		inline virtual float getBeginX() override { return label ? std::min(hb->x, hb->x + label->getTextXPos()) : hb->x; }
		inline virtual float getBeginY() override { return label ? std::min(hb->y, hb->y + label->getTextYPos()) : hb->y; }
		inline strv getLabelText() const { return label ? label->getText() : ""; }

		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
		UITitledInteractable& withLabel(strv text, FFont& font = cct.fontBold(), float xOff = 0, float yOff = -80, sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK);
	private:
		float xOff = 0;
		float yOff = 0;
	};

	// Ensure that the label offsets remain in sync with the hitbox size
	void UITitledInteractable::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		if (label) {
			label->updateCache();
			label->setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
		}
	}

	void UITitledInteractable::renderImpl()
	{
		UIInteractable::renderImpl();
		if (label) {
			label->drawText(hb->x, hb->y);
		}
	}

	UITitledInteractable& UITitledInteractable::withLabel(strv text, FFont& font, float xOff, float yOff, sdl::Color color, sdl::Color colorOutline)
	{
		this->xOff = xOff;
		this->yOff = yOff;
		label = std::make_unique<TextInfo>(font, text, color, colorOutline);
		label->setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
		return *this;
	}
}