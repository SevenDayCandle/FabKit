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

		inline virtual float getScaleOffsetPosX() const override { return cfg.getScreenXSize() * offsetPosX / cfg.renderScale(); }
		inline virtual float getScaleOffsetPosY() const override { return cfg.getScreenYSize() * offsetPosY / cfg.renderScale(); }
		inline virtual float getScaleOffsetSizeX() const override { return cfg.getScreenXSize() * offsetSizeX / cfg.renderScale(); }
		inline virtual float getScaleOffsetSizeY() const override { return cfg.getScreenYSize() * offsetSizeY / cfg.renderScale(); }

	protected:
		inline void refreshExactPosX() override { x = cfg.getScreenXSize() * offsetPosX; }
		inline void refreshExactPosY() override { y = cfg.getScreenYSize() * offsetPosY; }
		inline void refreshExactSizeX() override { w = cfg.getScreenXSize() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = cfg.getScreenYSize() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / cfg.getScreenXSize(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / cfg.getScreenYSize(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / cfg.getScreenXSize(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / cfg.getScreenYSize(); }
	};
}