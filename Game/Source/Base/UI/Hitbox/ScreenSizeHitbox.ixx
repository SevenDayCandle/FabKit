export module fbc.screenSizeHitbox;

import fbc.coreConfig;
import fbc.hitbox;

export namespace fbc {
	/* Hitbox whose position AND size scale with screen dimensions */
	export class ScreenSizeHitbox : public Hitbox {
	public:
		ScreenSizeHitbox() : ScreenSizeHitbox(0, 0, 1, 1) {}
		ScreenSizeHitbox(float offsetWidth, float offsetHeight) : ScreenSizeHitbox(0, 0, offsetWidth, offsetHeight) {}
		ScreenSizeHitbox(float screenXPercentPos, float screenYPercentPos, float screenXPercentSize, float screenYPercentSize) : Hitbox(screenXPercentPos, screenYPercentPos, screenXPercentSize, screenYPercentSize) {
			refresh();
		}
		~ScreenSizeHitbox() override {}

	protected:
		inline void refreshExactPosX() override { x = getScreenXSize() * offsetPosX; }
		inline void refreshExactPosY() override { y = getScreenYSize() * offsetPosY; }
		inline void refreshExactSizeX() override { w = getScreenXSize() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = getScreenYSize() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / getScreenXSize(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / getScreenYSize(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / getScreenXSize(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / getScreenYSize(); }
	};
}