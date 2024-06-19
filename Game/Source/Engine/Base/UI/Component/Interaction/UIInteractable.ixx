export module fbc.UIInteractable;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FSound;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.ScreenManager;
import fbc.UIImage;
import sdl;
import std;

export namespace fbc {
	export class UIInteractable : public UIImage {
	public:
		UIInteractable(Hitbox* hb, IDrawable& image) : UIImage(hb, image) {}
		UIInteractable(Hitbox* hb, IDrawable& image, sdl::Point origin) : UIImage(hb, image, origin) {}
		virtual ~UIInteractable() override {}

		bool interactable = true;
		FSound* soundClick = &cct.audio.uiClick;
		FSound* soundHover = nullptr;

		inline UIInteractable& setSoundClick(FSound* val) { return soundClick = val, *this; }
		inline UIInteractable& setSoundHover(FSound* val) { return soundHover = val, *this; }
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
				if (hb->isJust() && soundHover) {
					soundHover->play();
				}

				if (sdl::mouseIsLeftJustClicked() || sdl::mouseIsRightJustClicked()) {
					screenManager::activeElement = this;
				}
				else if (cfg.actSelect.isKeyJustPressed()) {
					if (soundClick) {
						soundClick->play();
					}
					clickLeftEvent();
					if (screenManager::activeElement == this) {
						screenManager::activeElement = nullptr;
					}
				}
			}
			else if (screenManager::activeElement == this) {
				if (sdl::mouseIsLeftJustReleased()) {
					if (soundClick) {
						soundClick->play();
					}
					clickLeftEvent();
					screenManager::activeElement = nullptr;
				}
				else if (sdl::mouseIsRightJustReleased()) {
					if (soundClick) {
						soundClick->play();
					}
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