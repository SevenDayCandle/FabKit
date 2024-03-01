export module fbc.screenHitbox;

import fbc;
import fbc.offsetHitbox;

export namespace fbc::hitbox {
	export class ScreenHitbox : OffsetHitbox {
	public:
		ScreenHitbox() {}
		ScreenHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): OffsetHitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refreshSize();
		}
		~ScreenHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the hitbox position in accordance to the screen's current size
	void ScreenHitbox::refreshPosition() {
		x = renderScale() * offsetX;
		y = renderScale() * offsetY;
	}

	// Set the hitbox dimensions in accordance to the screen's current size
	void ScreenHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}