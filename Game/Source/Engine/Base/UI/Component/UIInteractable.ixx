export module fbc.UIInteractable;

import fbc.futil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIImage;
import fbc.screenManager;
import sdl;
import std;

export namespace fbc {
	export class UIInteractable : public UIImage {
	public:
		UIInteractable(Hitbox* hb, IDrawable& image) : UIImage(hb, image) {}
		UIInteractable(Hitbox* hb, IDrawable& image, sdl::Point origin) : UIImage(hb, image, origin) {}
		virtual ~UIInteractable() override {}

		bool interactable = true;

		inline UIInteractable& setInteractable(bool val) { return interactable = val, *this; }
		virtual void updateImpl() override;
	protected:
		inline virtual void clickLeftEvent() {}
		inline virtual void clickRightEvent() {}
	};

	void UIInteractable::updateImpl()
	{
		UIImage::updateImpl();
		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && interactable) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (sdl::mouseIsLeftJustClicked() || sdl::mouseIsRightJustClicked()) {
					screenManager::activeElement = this;
				}
			}
			else if (screenManager::activeElement == this) {
				if (sdl::mouseIsLeftJustReleased()) {
					clickLeftEvent();
					screenManager::activeElement = nullptr;
				}
				else if (sdl::mouseIsRightJustReleased()) {
					clickRightEvent();
					screenManager::activeElement = nullptr;
				}
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased() || sdl::mouseIsRightJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}
}