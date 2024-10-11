export module fab.ScreenPosHitbox;

import fab.FWindow;
import fab.Hitbox;

namespace fab {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenPosHitbox : public Hitbox {
	public:
		ScreenPosHitbox(FWindow& win) : Hitbox(win, 0, 0, 0, 0) {}
		ScreenPosHitbox(FWindow& win, float offsetWidth, float offsetHeight) : ScreenPosHitbox(win, 0, 0, offsetWidth, offsetHeight) {}
		ScreenPosHitbox(FWindow& win, float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(win, screenXPercent, screenYPercent, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScreenPosHitbox() override {}


		inline virtual float getScaleOffPosX() const override { return win.getW() * offPosX / win.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return win.getH() * offPosY / win.renderScale(); }
	protected:
		inline void refreshOffPosX() override { offPosX = x / win.getW(); }
		inline void refreshOffPosY() override { offPosY = y / win.getH(); }
		inline void refreshOffSizeX() override { offSizeX = w / win.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / win.renderScale(); }
		inline void refreshRealPosX() override { x = win.getW() * offPosX; }
		inline void refreshRealPosY() override { y = win.getH() * offPosY; }
		inline void refreshRealSizeX() override { w = win.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = win.renderScale() * offSizeY; }
	};
}