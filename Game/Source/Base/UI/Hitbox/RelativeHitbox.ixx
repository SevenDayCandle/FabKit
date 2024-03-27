export module fbc.relativeHitbox;

import fbc.coreConfig;
import fbc.hitbox;
import fbc.hitbox;
import fbc.futil;

export namespace fbc {
	export class RelativeHitbox : public Hitbox {
	public:
		RelativeHitbox(Hitbox& parent) : parent(parent) {
			RelativeHitbox::refreshSize();
		}
		RelativeHitbox(Hitbox& parent, float offsetX, float offsetY, float offsetWidth, float offsetHeight) : parent(parent), Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			RelativeHitbox::refreshSize();
		}
		~RelativeHitbox() override {}
	protected:
		Hitbox& parent;
		void refreshPosition() override;
		void refreshSize() override;
	};

	// Refresh coordinates starting from parent's starting coordinates
	void RelativeHitbox::refreshPosition()
	{
		x = parent.x + renderScale() * offsetX;
		y = parent.y + renderScale() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void RelativeHitbox::refreshSize() {
		w = renderScale() * offsetWidth;
		h = renderScale() * offsetHeight;
		refreshPosition();
	}
}