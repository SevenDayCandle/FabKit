export module fbc.ScreenSizeHitbox;

import fbc.CoreConfig;
import fbc.Hitbox;

namespace fbc {
	/* Hitbox whose position AND size scale with screen dimensions */
	export class ScreenSizeHitbox : public Hitbox {
	public:
		ScreenSizeHitbox() : ScreenSizeHitbox(0, 0, 1, 1) {}
		ScreenSizeHitbox(float offsetWidth, float offsetHeight) : ScreenSizeHitbox(0, 0, offsetWidth, offsetHeight) {}
		ScreenSizeHitbox(float screenXPercentPos, float screenYPercentPos, float screenXPercentSize, float screenYPercentSize) : Hitbox(screenXPercentPos, screenYPercentPos, screenXPercentSize, screenYPercentSize) {
			refresh();
		}
		~ScreenSizeHitbox() override {}

		inline virtual float getScaleOffPosX() const override { return cfg.getScreenXSize() * offPosX / cfg.renderScale(); }
		inline virtual float getScaleOffPosY() const override { return cfg.getScreenYSize() * offPosY / cfg.renderScale(); }
		inline virtual float getScaleOffSizeX() const override { return cfg.getScreenXSize() * offSizeX / cfg.renderScale(); }
		inline virtual float getScaleOffSizeY() const override { return cfg.getScreenYSize() * offSizeY / cfg.renderScale(); }

	protected:
		inline void refreshOffPosX() override { offPosX = x / cfg.getScreenXSize(); }
		inline void refreshOffPosY() override { offPosY = y / cfg.getScreenYSize(); }
		inline void refreshOffSizeX() override { offSizeX = w / cfg.getScreenXSize(); }
		inline void refreshOffSizeY() override { offSizeY = h / cfg.getScreenYSize(); }
		inline void refreshRealPosX() override { x = cfg.getScreenXSize() * offPosX; }
		inline void refreshRealPosY() override { y = cfg.getScreenYSize() * offPosY; }
		inline void refreshRealSizeX() override { w = cfg.getScreenXSize() * offSizeX; }
		inline void refreshRealSizeY() override { h = cfg.getScreenYSize() * offSizeY; }
	};
}