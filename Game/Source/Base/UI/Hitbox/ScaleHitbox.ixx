export module fbc.scaleHitbox;

import fbc.hitbox;
import fbc.coreConfig;

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
		inline void refreshExactPosX() override { x = renderScale() * offsetPosX; }
		inline void refreshExactPosY() override { y = renderScale() * offsetPosY; }
		inline void refreshExactSizeX() override { w = renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = x / renderScale(); }
		inline void refreshOffsetPosY() override { offsetPosY = y / renderScale(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / renderScale(); }
	};
}