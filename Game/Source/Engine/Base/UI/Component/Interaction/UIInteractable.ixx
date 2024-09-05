export module fbc.UIInteractable;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FSound;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;

import fbc.UIImage;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIInteractable : public UIImage {
	public:
		UIInteractable(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image, FSound* soundClick, FSound* soundHover) : UIImage(window, move(hb), image), soundClick(soundClick), soundHover(soundHover) {}
		UIInteractable(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIInteractable(window, move(hb), image, &window.cct.audio.uiClick, nullptr) {}

		bool interactable = true;
		FSound* soundClick;
		FSound* soundHover;

		inline UIInteractable& setSoundClick(FSound* val) { return soundClick = val, *this; }
		inline UIInteractable& setSoundHover(FSound* val) { return soundHover = val, *this; }
		inline UIInteractable& setInteractable(bool val) { return interactable = val, *this; }
		virtual void updateImpl() override;
	protected:
		inline virtual void clickLeftEvent() {}
		inline virtual void clickRightEvent() {}
		inline virtual void justHoveredEvent() {}
		inline virtual void justUnhoveredEvent() {}
	};

	void UIInteractable::updateImpl()
	{
		UIImage::updateImpl();
		if (hb->isHovered()) {
			if (this->win.activeElement == nullptr && interactable) {
				if (hb->isJust()) {
					if (soundHover) {
						soundHover->play();
					}
					justHoveredEvent();
				}

				if (sdl::runner::mouseIsLeftJustClicked() || sdl::runner::mouseIsRightJustClicked()) {
					this->win.activeElement = this;
				}
				else if (win.cfg.actSelect.isKeyJustPressed()) {
					if (soundClick) {
						soundClick->play();
					}
					clickLeftEvent();
					if (this->win.activeElement == this) {
						this->win.activeElement = nullptr;
					}
				}
			}
			else if (this->win.activeElement == this) {
				if (sdl::runner::mouseIsLeftJustReleased()) {
					if (soundClick) {
						soundClick->play();
					}
					clickLeftEvent();
					this->win.activeElement = nullptr;
				}
				else if (sdl::runner::mouseIsRightJustReleased()) {
					if (soundClick) {
						soundClick->play();
					}
					clickRightEvent();
					this->win.activeElement = nullptr;
				}
			}
		}
		else if (this->win.activeElement == this && (sdl::runner::mouseIsLeftJustReleased() || sdl::runner::mouseIsRightJustReleased())) {
			this->win.activeElement = nullptr;
		}
		else if (hb->isJust() && interactable) {
			justUnhoveredEvent();
		}
	}
}