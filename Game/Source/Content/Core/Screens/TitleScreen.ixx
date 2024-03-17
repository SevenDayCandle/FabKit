export module fbc.titleScreen;

import fbc.coreContent;
import fbc.canvasScreen;
import fbc.screenHitbox;
import fbc.uiButton;
import fbc.futil;
import std;

export namespace fbc {
	export class TitleScreen : public CanvasScreen {
	public:
		TitleScreen() {
			canvas.addElement(std::make_unique<UIButton>(new ScreenHitbox(), cct.images.squareButton()));
		}

		void close() {

		}

		void open() {

		}
	};
}