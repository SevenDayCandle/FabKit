export module fbc.RelativeHitbox;

import fbc.CoreConfig;
import fbc.Hitbox;
import fbc.Hitbox;
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

		inline void refreshExactPosX() override { x = parent.x + cfg.renderScale() * offsetPosX; }
		inline void refreshExactPosY() override { y = parent.y + cfg.renderScale() * offsetPosY; }
		inline void refreshExactSizeX() override { w = cfg.renderScale() * offsetSizeX; }
		inline void refreshExactSizeY() override { h = cfg.renderScale() * offsetSizeY; }
		inline void refreshOffsetPosX() override { offsetPosX = (x - parent.x) / cfg.renderScale(); }
		inline void refreshOffsetPosY() override { offsetPosY = (y - parent.y) / cfg.renderScale(); }
		inline void refreshOffsetSizeX() override { offsetSizeX = w / cfg.renderScale(); }
		inline void refreshOffsetSizeY() override { offsetSizeY = h / cfg.renderScale(); }

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