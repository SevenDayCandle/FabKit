export module fab.ScreenSizeHitbox;

import fab.FWindow;
import fab.Hitbox;

namespace fab {
	/* Hitbox whose position AND size scale with screen dimensions */
	export class ScreenSizeHitbox : public Hitbox {
	public:
		ScreenSizeHitbox(FWindow& win) : ScreenSizeHitbox(win, 0, 0, 1, 1) {}
		ScreenSizeHitbox(FWindow& win, float offsetWidth, float offsetHeight) : ScreenSizeHitbox(win, 0, 0, offsetWidth, offsetHeight) {}
		ScreenSizeHitbox(FWindow& win, float screenXPercentPos, float screenYPercentPos, float screenXPercentSize, float screenYPercentSize) : Hitbox(win, screenXPercentPos, screenYPercentPos, screenXPercentSize, screenYPercentSize) {
			refresh();
		}
		~ScreenSizeHitbox() override {}

		inline virtual float getScaleOffPosX() const override { return win.getW() * offPosX / win.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return win.getH() * offPosY / win.renderScale(); }
		inline virtual float getScaleOffSizeX() const override { return win.getW() * offSizeX / win.renderScale(); }
		inline virtual float getScaleOffSizeY() const override { return win.getH() * offSizeY / win.renderScale(); }
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