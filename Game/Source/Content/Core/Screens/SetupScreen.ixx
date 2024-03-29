export module fbc.setupScreen;

import fbc.canvasScreen;
import fbc.coreContent;
import fbc.futil;
import fbc.screenHitbox;
import fbc.screenManager;
import fbc.uiTextButton;

export namespace fbc {
	export class SetupScreen : public CanvasScreen {
	public:
		SetupScreen(): CanvasScreen() {
			UITextButton& b = canvas.addElement(std::make_unique<UITextButton>(
				new ScreenHitbox(0.25f, 0.5f, 130, 100),
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.ui_close()));
			b.setOnClick([](UIButton& i) {
				screenManager::closeCurrentScreen();
			});
		}

		void close() {

		}

		void open() {

		}
	};
}