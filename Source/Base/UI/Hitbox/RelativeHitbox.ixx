export module fab.RelativeHitbox;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;

namespace fab {
	export class RelativeHitbox : public Hitbox {
	public:
		RelativeHitbox(FWindow& win, Hitbox& parent) : RelativeHitbox(win, parent, 0, 0, 0, 0) {}
		RelativeHitbox(FWindow& win, Hitbox& parent, float offsetWidth, float offsetHeight) : RelativeHitbox(win, parent, 0, 0, offsetWidth, offsetHeight) {}
		RelativeHitbox(FWindow& win, Hitbox& parent, float parentOffsetX, float parentOffsetY, float offsetWidth, float offsetHeight) : parent(parent), Hitbox(win, parentOffsetX, parentOffsetY, offsetWidth, offsetHeight) {
			refresh();
		}
		~RelativeHitbox() override {}

		inline float toOffPosX(float rX) const override { return (rX - parent.x) / win.renderScale(); }
		inline float toOffPosY(float rY) const override { return (rY - parent.y) / win.renderScale(); }
		inline float toRealPosX(float offX) const override { return parent.x + win.renderScale() * offX; }
		inline float toRealPosY(float offY) const override { return parent.y + win.renderScale() * offY; }

		inline static uptr<RelativeHitbox> make(FWindow& win, Hitbox& parent) { return make_unique<RelativeHitbox>(win, parent); }
		inline static uptr<RelativeHitbox> make(FWindow& win, Hitbox& parent, float offsetWidth, float offsetHeight) { return make_unique<RelativeHitbox>(win, parent, offsetWidth, offsetHeight); }
		inline static uptr<RelativeHitbox> make(FWindow& win, Hitbox& parent, float parentOffsetX, float parentOffsetY, float offsetWidth, float offsetHeight) { return make_unique<RelativeHitbox>(win, parent, parentOffsetX, parentOffsetY, offsetWidth, offsetHeight); }
	protected:
		Hitbox& parent;

		inline void refreshOffPosX() override { offPosX = (x - parent.x) / win.renderScale(); }
		inline void refreshOffPosY() override { offPosY = (y - parent.y) / win.renderScale(); }
		inline void refreshOffSizeX() override { offSizeX = w / win.renderScale(); }
		inline void refreshOffSizeY() override { offSizeY = h / win.renderScale(); }
		inline void refreshRealPosX() override { x = parent.x + win.renderScale() * offPosX; }
		inline void refreshRealPosY() override { y = parent.y + win.renderScale() * offPosY; }
		inline void refreshRealSizeX() override { w = win.renderScale() * offSizeX; }
		inline void refreshRealSizeY() override { h = win.renderScale() * offSizeY; }

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