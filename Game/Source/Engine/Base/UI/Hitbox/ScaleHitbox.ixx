export module fbc.ScaleHitbox;

import fbc.Hitbox;
import fbc.CoreConfig;

export namespace fbc {
	export class ScaleHitbox : public Hitbox {
	public:
		ScaleHitbox() : Hitbox(0, 0, 0, 0) {}
		ScaleHitbox(float offsetWidth, float offsetHeight) : ScaleHitbox(0, 0, offsetWidth, offsetHeight) {}
		ScaleHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~ScaleHitbox() override {}

	protected:
		inline void refreshExactPosX() override { x = cfg.renderScale() * offsetPosX; }
		inline void refreshExactPosY() override { y = cfg.renderScale() * offsetPosY; }
		inline void refreshExactSizeX() override { w = cfg.renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = cfg.renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / cfg.renderScale(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / cfg.renderScale(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / cfg.renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / cfg.renderScale(); }
	};
}