export module fbc.ScreenPosHitbox;

import fbc.CoreConfig;
import fbc.FWindow;
import fbc.Hitbox;

namespace fbc {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenPosHitbox : public Hitbox {
	public:
		ScreenPosHitbox(FWindow& window) : Hitbox(0, 0, 0, 0), win(window) {}
		ScreenPosHitbox(FWindow& window, float offsetWidth, float offsetHeight) : ScreenPosHitbox(window, 0, 0, offsetWidth, offsetHeight) {}
		ScreenPosHitbox(FWindow& window, float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(screenXPercent, screenYPercent, offsetWidth, offsetHeight), win(window) {
			refresh();
		}
		~ScreenPosHitbox() override {}

		FWindow& win;

		inline virtual float getScaleOffPosX() const override { return win.getW() * offPosX / cfg.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return win.getH() * offPosY / cfg.renderScale(); }
	protected:
		inline void refreshOffPosX() override { offPosX = x / win.getW(); }
		inline void refreshOffPosY() override { offPosY = y / win.getH(); }
		inline void refreshOffSizeX() override { offSizeX = w / cfg.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / cfg.renderScale(); }
		inline void refreshRealPosX() override { x = win.getW() * offPosX; }
		inline void refreshRealPosY() override { y = win.getH() * offPosY; }
		inline void refreshRealSizeX() override { w = cfg.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = cfg.renderScale() * offSizeY; }
	};
}