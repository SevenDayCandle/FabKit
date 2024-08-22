export module fbc.RelativeHitbox;

import fbc.CoreConfig;
import fbc.Hitbox;
import fbc.FUtil;

namespace fbc {
	export class RelativeHitbox : public Hitbox {
	public:
		RelativeHitbox(Hitbox& parent) : RelativeHitbox(parent, 0, 0, 0, 0) {}
		RelativeHitbox(Hitbox& parent, float offsetWidth, float offsetHeight) : RelativeHitbox(parent, 0, 0, offsetWidth, offsetHeight) {}
		RelativeHitbox(Hitbox& parent, float parentOffsetX, float parentOffsetY, float offsetWidth, float offsetHeight) : parent(parent), Hitbox(parentOffsetX, parentOffsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~RelativeHitbox() override {}

		inline static uptr<RelativeHitbox> make(Hitbox& parent) { return make_unique<RelativeHitbox>(parent); }
		inline static uptr<RelativeHitbox> make(Hitbox& parent, float offsetWidth, float offsetHeight) { return make_unique<RelativeHitbox>(parent, offsetWidth, offsetHeight); }
		inline static uptr<RelativeHitbox> make(Hitbox& parent, float parentOffsetX, float parentOffsetY, float offsetWidth, float offsetHeight) { return make_unique<RelativeHitbox>(parent, parentOffsetX, parentOffsetY, offsetWidth, offsetHeight); }
	protected:
		Hitbox& parent;

		inline void refreshOffPosX() override { offPosX = (x - parent.x) / cfg.renderScale(); }
		inline void refreshOffPosY() override { offPosY = (y - parent.y) / cfg.renderScale(); }
		inline void refreshOffSizeX() override { offSizeX = w / cfg.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / cfg.renderScale(); }
		inline void refreshRealPosX() override { x = parent.x + cfg.renderScale() * offPosX; }
		inline void refreshRealPosY() override { y = parent.y + cfg.renderScale() * offPosY; }
		inline void refreshRealSizeX() override { w = cfg.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = cfg.renderScale() * offSizeY; }

		void update() override;
	};

	// Position should always remain relative to the parent
	void RelativeHitbox::update()
	{
		Hitbox::update();
		refreshRealPosX();
		refreshRealPosY();
	}
}