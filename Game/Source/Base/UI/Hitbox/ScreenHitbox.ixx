export module fbc.screenHitbox;

import fbc.coreConfig;
import fbc.hitbox;

export namespace fbc {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenHitbox : public Hitbox {
	public:
		ScreenHitbox(): Hitbox(0, 0, 1, 1) {}
		ScreenHitbox(float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(screenXPercent, screenYPercent, offsetWidth, offsetHeight) {
			ScreenHitbox::refreshSize();
		}
		~ScreenHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the ui position in accordance to the screen's current size
	void ScreenHitbox::refreshPosition() {
		x = getScreenXSize() * offsetX;
		y = getScreenYSize() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void ScreenHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}