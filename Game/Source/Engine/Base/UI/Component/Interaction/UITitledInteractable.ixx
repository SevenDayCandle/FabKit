export module fbc.UITitledInteractable;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class UITitledInteractable : public UIInteractable {
	public:
		UITitledInteractable(FWindow& window, Hitbox* hb, IDrawable& image) : UIInteractable(window, hb, image) {}

		uptr<TextInfo> label;

		inline virtual float getBeginX() override { return label ? std::min(hb->x, hb->x + label->getTextXPos()) : hb->x; }
		inline virtual float getBeginY() override { return label ? std::min(hb->y, hb->y + label->getTextYPos()) : hb->y; }
		inline strv getLabelText() const { return label ? label->getText() : ""; }

		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		UITitledInteractable& withLabel(strv text, FFont& font = cct.fontBold(), float xOff = 0, float yOff = -80, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK);
	private:
		float xOff = 0;
		float yOff = 0;
	};

	// Ensure that the label offsets remain in sync with the hitbox size
	void UITitledInteractable::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		if (label) {
			label->refreshCache();
			label->setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
		}
	}

	void UITitledInteractable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
		if (label) {
			label->drawText(rp, hb->x, hb->y, win.getW(), win.getH());
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