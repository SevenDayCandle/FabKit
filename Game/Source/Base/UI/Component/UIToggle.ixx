export module fbc.UIToggle;

import fbc.ffont;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.uiImage;
import fbc.screenManager;
import fbc.textInfo;
import fbc.futil;
import sdl;

export namespace fbc {
	export class UIToggle : public UIImage, public TextInfo {
	public:
		UIToggle(Hitbox* hb, IDrawable& image, IDrawable& offImage, FFont& f): UIImage(hb, image), checkImage(offImage), TextInfo(f) {}
		UIToggle(Hitbox* hb, IDrawable& image, IDrawable& offImage, FFont& f, str text) : UIImage(hb, image), checkImage(offImage), TextInfo(f, text) {}
		virtual ~UIToggle() {}

		bool toggled;
		IDrawable& checkImage;

		inline bool isInteractable() { return interactable; }
		inline UIToggle& setInteractable(bool val) { return this->interactable = val, *this; }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		void renderImpl() override;
		void toggle(bool val);
		void updateImpl() override;
	private:
		func<void(UIToggle&)> onClick;
		bool interactable = true;
	};

	void UIToggle::renderImpl()
	{
		this->UITipHoverable::renderImpl();

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

		float textX = hb->x + hb->w * 1.5f;
		TextInfo::drawText(textX, hb->y);
	}

	void UIToggle::toggle(bool val)
	{
		toggled = val;
		if (onClick) {
			onClick(*this);
		}
	}

	void UIToggle::updateImpl()
	{
		UIImage::updateImpl();

		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && isInteractable()) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (sdl::mouseIsLeftJustClicked()) {
					screenManager::activeElement = this;
				}
			}
			else if (screenManager::activeElement == this) {
				if (sdl::mouseIsLeftJustReleased() && this->onClick) {
					toggle(!toggled);
				}
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}
}