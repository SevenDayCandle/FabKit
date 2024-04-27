export module fbc.screenPosHitbox;

import fbc.coreConfig;
import fbc.hitbox;

export namespace fbc {
	/* Hitbox whose position scale with screen dimensions, and whose size scale with render scale */
	export class ScreenPosHitbox : public Hitbox {
	public:
		ScreenPosHitbox() : Hitbox(0, 0, 0, 0) {}
		ScreenPosHitbox(float offsetWidth, float offsetHeight) : ScreenPosHitbox( 0, 0, offsetWidth, offsetHeight) {}
		ScreenPosHitbox(float screenXPercent, float screenYPercent, float offsetWidth, float offsetHeight): Hitbox(screenXPercent, screenYPercent, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScreenPosHitbox() override {}

	protected:
		inline void refreshExactPosX() override { x = getScreenXSize() * offsetPosX; }
		inline void refreshExactPosY() override { y = getScreenYSize() * offsetPosY; }
		inline void refreshExactSizeX() override { w = renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / getScreenXSize(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / getScreenYSize(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / renderScale(); }
	};
}