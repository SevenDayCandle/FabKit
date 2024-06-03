export module fbc.ScreenPosHitbox;

import fbc.CoreConfig;
import fbc.Hitbox;

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

		inline virtual float getScaleOffsetPosX() const override { return cfg.getScreenXSize() * offsetPosX / cfg.renderScale(); }
		inline virtual float getScaleOffsetPosY() const override { return cfg.getScreenYSize() * offsetPosY / cfg.renderScale(); }

	protected:
		inline void refreshExactPosX() override { x = cfg.getScreenXSize() * offsetPosX; }
		inline void refreshExactPosY() override { y = cfg.getScreenYSize() * offsetPosY; }
		inline void refreshExactSizeX() override { w = cfg.renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = cfg.renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / cfg.getScreenXSize(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / cfg.getScreenYSize(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / cfg.renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / cfg.renderScale(); }
	};
}