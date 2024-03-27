export module fbc.screenSizeHitbox;

import fbc.coreConfig;
import fbc.hitbox;

export namespace fbc {
	/* Hitbox whose position AND size scale with screen dimensions */
	export class ScreenSizeHitbox : public Hitbox {
	public:
		ScreenSizeHitbox() : Hitbox(0, 0, 1, 1) {}
		ScreenSizeHitbox(float screenXPercentPos, float screenYPercentPos, float screenXPercentSize, float screenYPercentSize) : Hitbox(screenXPercentPos, screenYPercentPos, screenXPercentSize, screenYPercentSize) {
			ScreenSizeHitbox::refreshSize();
		}
		~ScreenSizeHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the ui position in accordance to the screen's current size
	void ScreenSizeHitbox::refreshPosition() {
		x = getScreenXSize() * offsetX;
		y = getScreenYSize() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void ScreenSizeHitbox::refreshSize() {
		w = getScreenXSize() * offsetWidth;
		h = getScreenYSize() * offsetHeight;
		refreshPosition();
	}
}