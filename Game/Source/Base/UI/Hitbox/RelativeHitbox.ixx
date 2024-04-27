export module fbc.relativeHitbox;

import fbc.coreConfig;
import fbc.hitbox;
import fbc.hitbox;
import fbc.futil;

export namespace fbc {
	export class RelativeHitbox : public Hitbox {
	public:
		RelativeHitbox(Hitbox& parent) : RelativeHitbox(parent, 0, 0, 0, 0) {}
		RelativeHitbox(Hitbox& parent, float offsetWidth, float offsetHeight) : RelativeHitbox(parent, 0, 0, offsetWidth, offsetHeight) {}
		RelativeHitbox(Hitbox& parent, float parentOffsetX, float parentOffsetY, float offsetWidth, float offsetHeight) : parent(parent), Hitbox(parentOffsetX, parentOffsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~RelativeHitbox() override {}
	protected:
		Hitbox& parent;

		inline void refreshExactPosX() override { x = parent.x + renderScale() * offsetPosX; }
		inline void refreshExactPosY() override { y = parent.y + renderScale() * offsetPosY; }
		inline void refreshExactSizeX() override { w = renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = (x - parent.x) / renderScale(); }
		inline void refreshOffsetPosY() override { offsetPosY = (y - parent.y) / renderScale(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / renderScale(); }

		void update() override;
	};

	// Position should always remain relative to the parent
	void RelativeHitbox::update()
	{
		Hitbox::update();
		refreshExactPosX();
		refreshExactPosY();
	}
}