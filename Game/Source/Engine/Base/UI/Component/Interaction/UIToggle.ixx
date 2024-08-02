export module fbc.UIToggle;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class UIToggle : public UIInteractable, public TextInfo {
	public:
		UIToggle(Hitbox* hb, strv text, IDrawable& image = cct.images.uiCheckboxEmpty, IDrawable& checkImage = cct.images.uiCheckboxFilled, FFont& f = cct.fontRegular(), float xOff = cct.images.uiCheckboxEmpty.getWidth() * 1.15f, float yOff = cct.images.uiCheckboxEmpty.getHeight() * 0.25f):
			UIInteractable(hb, image), checkImage(checkImage), TextInfo(f, text), xOff(xOff), yOff(yOff) {
			UIToggle::onSizeUpdated();
		}

		bool toggled = false;
		IDrawable& checkImage;

		inline float getBeginX() override { return std::min(hb->x, hb->x + getTextXPos()); }
		inline float getBeginY() override { return std::min(hb->y, hb->y + getTextYPos()); }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setTextOffsetX(float xOff) { return this->xOff = xOff, *this; }
		inline UIToggle& setTextOffsetY(float yOff) { return this->yOff = yOff, *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		void onSizeUpdated() override;
		void refreshDimensions() override;
		void renderImpl() override;
		void toggle(bool val);
	private:
		func<void(UIToggle&)> onClick;
		float xOff = 0;
		float yOff = 0;

		virtual void clickLeftEvent() override;
	};

	void UIToggle::onSizeUpdated()
	{
		TextInfo::setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
	}

	void UIToggle::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		refreshCache();
	}

	void UIToggle::renderImpl()
	{
		if (toggled) {
			checkImage.draw(hb.get(), UIImage::color, origin, rotation, flip);
			if (hb->isHovered()) {
				checkImage.draw(hb.get(), sdl::BlendMode::SDL_BLENDMODE_ADD, UIImage::color, origin, rotation, flip);
			}
		}
		else {
			image.draw(hb.get(), UIImage::color, origin, rotation, flip);
			if (hb->isHovered()) {
				image.draw(hb.get(), sdl::BlendMode::SDL_BLENDMODE_ADD, UIImage::color, origin, rotation, flip);
			}
		}

		TextInfo::drawText(hb->x, hb->y);
	}

	void UIToggle::toggle(bool val)
	{
		toggled = val;
		if (onClick) {
			onClick(*this);
		}
	}

	void UIToggle::clickLeftEvent()
	{
		toggle(!toggled);
	}
}