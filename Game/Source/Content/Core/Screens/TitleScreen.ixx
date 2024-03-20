export module fbc.titleScreen;

import fbc.coreContent;
import fbc.canvasScreen;
import fbc.screenSizeHitbox;
import fbc.uiButton;
import fbc.futil;
import std;

export namespace fbc {
	export class TitleScreen : public CanvasScreen {
	public:
		TitleScreen() {
			canvas.addElement(std::make_unique<UIButton>(new ScreenSizeHitbox(0.25f, 0.25f, 0.5f, 0.5f), fbc::cct.images.smallPanel));
		}

		void close() {

		}

		void open() {

		}
	};
}