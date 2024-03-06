export module fbc.screenHitbox;

import fbc;
import fbc.hitbox;

export namespace fbc::ui {
	export class ScreenHitbox : Hitbox {
	public:
		ScreenHitbox() {}
		ScreenHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refreshSize();
		}
		~ScreenHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the ui position in accordance to the screen's current size
	void ScreenHitbox::refreshPosition() {
		x = fbc::getScreenXSize() * offsetX;
		y = fbc::getScreenYSize() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void ScreenHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}