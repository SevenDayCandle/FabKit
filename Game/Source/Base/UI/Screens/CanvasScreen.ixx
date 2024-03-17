export module fbc.canvasScreen;

import fbc.baseScreen;
import fbc.futil;
import fbc.uiCanvas;
import fbc.hitbox;
import fbc.screenHitbox;
import std;

export namespace fbc {
	export class CanvasScreen : public BaseScreen {
	public:
		CanvasScreen() : canvas{ new ScreenHitbox()} {}
		CanvasScreen(Hitbox* hb) : canvas{hb} {}
		virtual ~CanvasScreen() {}

		UICanvas canvas;

		virtual void render() override;
		virtual void update() override;
	};

	// Update items in the canvas. Canvas should never be disabled
	void CanvasScreen::render() {
		canvas.renderImpl();
	}

	// Update items in the canvas. Canvas should never be disabled
	void CanvasScreen::update() {
		canvas.updateImpl();
	}
}