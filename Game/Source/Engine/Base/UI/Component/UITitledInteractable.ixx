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

		virtual void refreshRenderables() override;
		virtual void renderImpl() override;
		UITitledInteractable& withLabel(strv text, FFont& font = cct.fontBold(), float x = 0, float y = cfg.renderScale(-80), sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK);
	};

	void UITitledInteractable::refreshRenderables()
	{
		UIInteractable::refreshRenderables();
		if (label) {
			label->updateCache();
		}
	}

	void UITitledInteractable::renderImpl()
	{
		UIInteractable::renderImpl();
		if (label) {
			label->drawText(hb->x, hb->y);
		}
	}

	UITitledInteractable& UITitledInteractable::withLabel(strv text, FFont& font, float x, float y, sdl::Color color, sdl::Color colorOutline)
	{
		label = std::make_unique<TextInfo>(font, text, color, colorOutline);
		label->setPos(x, y);
		return *this;
	}
}