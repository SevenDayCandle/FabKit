export module fbc.UIToggle;

import fbc.CoreContent;
import fbc.FFont;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.ScreenManager;
import fbc.TextInfo;
import fbc.FUtil;
import sdl;

export namespace fbc {
	export class UIToggle : public UIInteractable, public TextInfo {
	public:
		UIToggle(Hitbox* hb, str text, IDrawable& image = cct.images.checkboxEmpty(), IDrawable& checkImage = cct.images.checkboxFilled(), FFont& f = cct.fontRegular()):
			UIInteractable(hb, image), checkImage(checkImage), TextInfo(f, text) {
			UIToggle::onSizeUpdated();
		}
		virtual ~UIToggle() {}

		bool toggled = false;
		IDrawable& checkImage;

		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		virtual void onSizeUpdated() override;
		void renderImpl() override;
		void toggle(bool val);
	private:
		func<void(UIToggle&)> onClick;

		virtual void clickLeftEvent() override;
	};

	void UIToggle::onSizeUpdated()
	{
		TextInfo::setPos(this->hb->w * 1.5f, this->hb->h * 0.5f);
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