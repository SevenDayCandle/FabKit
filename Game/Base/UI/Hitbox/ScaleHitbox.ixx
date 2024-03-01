export module fbc.scaleHitbox;

import fbc;
import fbc.offsetHitbox;

export namespace fbc::hitbox {
	export class ScaleHitbox : OffsetHitbox {
	public:
		ScaleHitbox() {}
		ScaleHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): OffsetHitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refreshSize();
		}
		~ScaleHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the hitbox position in accordance to the screen's current size
	void ScaleHitbox::refreshPosition() {
		x = renderScale() * offsetX;
		y = renderScale() * offsetY;
	}

	// Set the hitbox dimensions in accordance to the screen's current size
	void ScaleHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}