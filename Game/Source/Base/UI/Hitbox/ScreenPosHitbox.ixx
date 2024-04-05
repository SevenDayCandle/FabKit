export module fbc.screenPosHitbox;

import fbc.coreConfig;
import fbc.hitbox;

export namespace fbc {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenPosHitbox : public Hitbox {
	public:
		ScreenPosHitbox() {}
		ScreenPosHitbox(float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(screenXPercent, screenYPercent, offsetWidth, offsetHeight) {
			ScreenPosHitbox::refreshSize();
		}
		~ScreenPosHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the ui position in accordance to the screen's current size
	void ScreenPosHitbox::refreshPosition() {
		x = getScreenXSize() * offsetX;
		y = getScreenYSize() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void ScreenPosHitbox::refreshSize() {
		w = renderScale() * offsetWidth;
		h = renderScale() * offsetHeight;
		refreshPosition();
	}
}