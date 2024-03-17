export module fbc.scaleHitbox;

import fbc.hitbox;
import fbc.coreConfig;

export namespace fbc {
	export class ScaleHitbox : public Hitbox {
	public:
		ScaleHitbox() {}
		ScaleHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight): Hitbox(offsetX, offsetY, offsetWidth, offsetHeight) {
			ScaleHitbox::refreshSize();
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