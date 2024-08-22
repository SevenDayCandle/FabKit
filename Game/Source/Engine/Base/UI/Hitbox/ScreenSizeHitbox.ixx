export module fbc.ScreenSizeHitbox;

import fbc.CoreConfig;
import fbc.FWindow;
import fbc.Hitbox;

namespace fbc {
	/* Hitbox whose position AND size scale with screen dimensions */
	export class ScreenSizeHitbox : public Hitbox {
	public:
		ScreenSizeHitbox(FWindow& window) : ScreenSizeHitbox(window, 0, 0, 1, 1) {}
		ScreenSizeHitbox(FWindow& window, float offsetWidth, float offsetHeight) : ScreenSizeHitbox(window, 0, 0, offsetWidth, offsetHeight) {}
		ScreenSizeHitbox(FWindow& window, float screenXPercentPos, float screenYPercentPos, float screenXPercentSize, float screenYPercentSize) : Hitbox(screenXPercentPos, screenYPercentPos, screenXPercentSize, screenYPercentSize), win(window) {
			refresh();
		}
		~ScreenSizeHitbox() override {}

		FWindow& win;

		inline virtual float getScaleOffPosX() const override { return win.getW() * offPosX / cfg.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return win.getH() * offPosY / cfg.renderScale(); }
		inline virtual float getScaleOffSizeX() const override { return win.getW() * offSizeX / cfg.renderScale(); }
		inline virtual float getScaleOffSizeY() const override { return win.getH() * offSizeY / cfg.renderScale(); }
	protected:
		inline void refreshOffPosX() override { offPosX = x / win.getW(); }
		inline void refreshOffPosY() override { offPosY = y / win.getH(); }
		inline void refreshOffSizeX() override { offSizeX = w / win.getW(); }
		inline void refreshOffSizeY() override { offSizeY = h / win.getH(); }
		inline void refreshRealPosX() override { x = win.getW() * offPosX; }
		inline void refreshRealPosY() override { y = win.getH() * offPosY; }
		inline void refreshRealSizeX() override { w = win.getW() * offSizeX; }
		inline void refreshRealSizeY() override { h = win.getH() * offSizeY; }
	};
}