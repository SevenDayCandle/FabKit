export module fbc.scaleHitbox;

import fbc;
import fbc.hitbox;

export namespace fbc::ui {
	export class ScaleHitbox : Hitbox {
	public:
		ScaleHitbox() {}
		ScaleHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			refreshSize();
		}
		~ScaleHitbox() override {}

	protected:
		void refreshSize() override;
		void refreshPosition() override;
	};

	// Set the ui position in accordance to the screen's current size
	void ScaleHitbox::refreshPosition() {
		x = renderScale() * offsetX;
		y = renderScale() * offsetY;
	}

	// Set the ui dimensions in accordance to the screen's current size
	void ScaleHitbox::refreshSize() {
		width = renderScale() * offsetWidth;
		height = renderScale() * offsetHeight;
		refreshPosition();
	}
}