export module fbc.ScaleHitbox;

import fbc.FWindow;
import fbc.Hitbox;

namespace fbc {
	export class ScaleHitbox : public Hitbox {
	public:
		ScaleHitbox(FWindow& win) : Hitbox(win, 0, 0, 0, 0) {}
		ScaleHitbox(FWindow& win, float offsetWidth, float offsetHeight) : ScaleHitbox(win, 0, 0, offsetWidth, offsetHeight) {}
		ScaleHitbox(FWindow& win, float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(win, offsetX, offsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScaleHitbox() override {}

	protected:
		inline void refreshOffPosX() override { offPosX = x / win.renderScale(); }
		inline void refreshOffPosY() override { offPosY = y / win.renderScale(); }
		inline void refreshOffSizeX() override { offSizeX = w / win.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / win.renderScale(); }
		inline void refreshRealPosX() override { x = win.renderScale() * offPosX; }
		inline void refreshRealPosY() override { y = win.renderScale() * offPosY; }
		inline void refreshRealSizeX() override { w = win.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = win.renderScale() * offSizeY; }
	};
}