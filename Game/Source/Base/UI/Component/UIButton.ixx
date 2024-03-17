export module fbc.uiButton;

import fbc.ftexture;
import fbc.futil;
import fbc.hitbox;
import fbc.uiImage;
import raylib;

export namespace fbc {
	export class UIButton : public UIImage {
	public:

		UIButton(Hitbox* hb, fbc::FTexture& image) : UIImage(hb, image) {}
		UIButton(Hitbox* hb, fbc::FTexture& image, raylib::Vector2 origin) : UIImage(hb, image, origin) {}
		~UIButton() override {}

		inline bool isInteractable() { return interactable; }
		inline UIButton& setInteractable(bool val) { return this->interactable = val, *this; }
		inline UIButton& setOnClick(const func<void(UIButton&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIButton& setOnRightClick(const func<void(UIButton&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }

		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		bool interactable;
	private:
		func<void(UIButton&)> onClick;
		func<void(UIButton&)> onRightClick;
	};

	void UIButton::renderImpl() {
		UIImage::renderImpl();
		// TODO highlight if hovered
	}

	void UIButton::updateImpl() {
		UIImage::updateImpl();

		if (isInteractable()) {
			if (hb->isHovered()) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (futil::hasLeftClicked() && this->onClick) {
					this->onClick(*this);
				}
				else if (futil::hasRightClicked() && this->onRightClick) {
					this->onRightClick(*this);
				}
			}
		}
	}
}
