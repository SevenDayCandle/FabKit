export module fbc.ScreenPosHitbox;

import fbc.CoreConfig;
import fbc.Hitbox;

namespace fbc {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenPosHitbox : public Hitbox {
	public:
		ScreenPosHitbox() : Hitbox(0, 0, 0, 0) {}
		ScreenPosHitbox(float offsetWidth, float offsetHeight) : ScreenPosHitbox( 0, 0, offsetWidth, offsetHeight) {}
		ScreenPosHitbox(float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(screenXPercent, screenYPercent, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScreenPosHitbox() override {}

		inline virtual float getScaleOffPosX() const override { return cfg.getScreenXSize() * offPosX / cfg.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return cfg.getScreenYSize() * offPosY / cfg.renderScale(); }

	protected:
		inline void refreshOffPosX() override { offPosX = x / cfg.getScreenXSize(); }
		inline void refreshOffPosY() override { offPosY = y / cfg.getScreenYSize(); }
		inline void refreshOffSizeX() override { offSizeX = w / cfg.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / cfg.renderScale(); }
		inline void refreshRealPosX() override { x = cfg.getScreenXSize() * offPosX; }
		inline void refreshRealPosY() override { y = cfg.getScreenYSize() * offPosY; }
		inline void refreshRealSizeX() override { w = cfg.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = cfg.renderScale() * offSizeY; }
	};
}