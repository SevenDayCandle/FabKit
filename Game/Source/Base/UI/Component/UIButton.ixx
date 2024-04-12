export module fbc.uiButton;

import fbc.futil;
import fbc.iDrawable;
import fbc.hitbox;
import fbc.screenManager;
import fbc.uiImage;
import sdl;

export namespace fbc {
	export class UIButton : public UIImage {
	public:

		UIButton(Hitbox* hb, IDrawable& image) : UIImage(hb, image) {}
		UIButton(Hitbox* hb, IDrawable& image, sdl::Point origin) : UIImage(hb, image, origin) {}
		~UIButton() override {}

		inline bool isInteractable() { return interactable; }
		inline UIButton& setInteractable(bool val) { return this->interactable = val, *this; }
		inline UIButton& setOnClick(const func<void(UIButton&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIButton& setOnRightClick(const func<void(UIButton&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }

		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		bool interactable = true;
	private:
		func<void(UIButton&)> onClick;
		func<void(UIButton&)> onRightClick;
	};

	void UIButton::renderImpl() {
		UIImage::renderImpl();
		if (hb->isHovered()) {
			image.draw(hb.get(), sdl::BlendMode::SDL_BLENDMODE_ADD, color, origin, rotation, flip);
		}
	}

	void UIButton::updateImpl() {
		UIImage::updateImpl();

		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && isInteractable()) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (sdl::mouseIsLeftJustClicked() || sdl::mouseIsRightJustClicked()) {
					screenManager::activeElement = this;
				}
			}
			else if (screenManager::activeElement == this) {
				if (sdl::mouseIsLeftJustReleased() && this->onClick) {
					this->onClick(*this);
					screenManager::activeElement = nullptr;
				}
				else if (sdl::mouseIsRightJustReleased() && this->onRightClick) {
					this->onRightClick(*this);
					screenManager::activeElement = nullptr;
				}
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased() || sdl::mouseIsRightJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}
}
