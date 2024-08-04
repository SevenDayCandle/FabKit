export module fbc.ScaleHitbox;

import fbc.Hitbox;
import fbc.CoreConfig;

namespace fbc {
	export class ScaleHitbox : public Hitbox {
	public:
		ScaleHitbox() : Hitbox(0, 0, 0, 0) {}
		ScaleHitbox(float offsetWidth, float offsetHeight) : ScaleHitbox(0, 0, offsetWidth, offsetHeight) {}
		ScaleHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScaleHitbox() override {}

	protected:
		inline void refreshOffPosX() override { offPosX = x / cfg.renderScale(); }
		inline void refreshOffPosY() override { offPosY = y / cfg.renderScale(); }
		inline void refreshOffSizeX() override { offSizeX = w / cfg.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / cfg.renderScale(); }
		inline void refreshRealPosX() override { x = cfg.renderScale() * offPosX; }
		inline void refreshRealPosY() override { y = cfg.renderScale() * offPosY; }
		inline void refreshRealSizeX() override { w = cfg.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = cfg.renderScale() * offSizeY; }
	};
}