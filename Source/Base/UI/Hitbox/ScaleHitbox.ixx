export module fab.ScaleHitbox;

import fab.FWindow;
import fab.Hitbox;

namespace fab {
	export class ScaleHitbox : public Hitbox {
	public:
		ScaleHitbox(FWindow& win) : Hitbox(win, 0, 0, 0, 0) {}
		ScaleHitbox(FWindow& win, float offsetWidth, float offsetHeight) : ScaleHitbox(win, 0, 0, offsetWidth, offsetHeight) {}
		ScaleHitbox(FWindow& win, float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(win, offsetX, offsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScaleHitbox() override {}

		inline float toOffPosX(float rX) const override { return (rX) / win.renderScale(); }
		inline float toOffPosY(float rY) const override { return (rY) / win.renderScale(); }
		inline float toRealPosX(float offX) const override { return win.renderScale() * offX; }
		inline float toRealPosY(float offY) const override { return win.renderScale() * offY; }

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