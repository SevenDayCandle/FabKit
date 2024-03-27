export module fbc.titleScreen;

import fbc.coreContent;
import fbc.canvasScreen;
import fbc.screenSizeHitbox;
import fbc.uiTextButton;
import fbc.futil;
import std;

export namespace fbc {
	export class TitleScreen : public CanvasScreen {
	public:
		TitleScreen() {
			canvas.addElement(std::make_unique<UITextButton>(
				new ScreenSizeHitbox(0.25f, 0.25f, 0.5f, 0.5f), 
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.screen_title_header()));
		}

		void close() {

		}

		void open() {

		}
	};
}