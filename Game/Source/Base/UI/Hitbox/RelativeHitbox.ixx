export module fbc.relativeHitbox;

import fbc;
import fbc.hitbox;
import fbc.hitbox;
import fbc.futil;

export namespace fbc::ui {
	export class RelativeHitbox : public Hitbox {
	public:
		RelativeHitbox(sptr<Hitbox> parent) : parent(parent) {
			RelativeHitbox::refreshSize();
		}
		RelativeHitbox(sptr<Hitbox> parent, float offsetX, float offsetY, float offsetWidth, float offsetHeight) : parent(parent), Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			RelativeHitbox::refreshSize();
		}
		~RelativeHitbox() override {}
	protected:
		sptr<Hitbox> parent;
		void refreshPosition() override;
		void refreshSize() override;
	};

	// Refresh coordinates starting from parent's starting coordinates
	void RelativeHitbox::refreshPosition()
	{
		x = parent->x + renderScale() * offsetX;
		y = parent->y + renderScale() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void RelativeHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}