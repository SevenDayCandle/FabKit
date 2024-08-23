export module fbc.ScaleHitbox;

import fbc.CoreConfig;
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
		inline void refreshOffPosX() override { offPosX = x / win.cfg.renderScale(); }
		inline void refreshOffPosY() override { offPosY = y / win.cfg.renderScale(); }
		inline void refreshOffSizeX() override { offSizeX = w / win.cfg.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / win.cfg.renderScale(); }
		inline void refreshRealPosX() override { x = win.cfg.renderScale() * offPosX; }
		inline void refreshRealPosY() override { y = win.cfg.renderScale() * offPosY; }
		inline void refreshRealSizeX() override { w = win.cfg.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = win.cfg.renderScale() * offSizeY; }
	};
}