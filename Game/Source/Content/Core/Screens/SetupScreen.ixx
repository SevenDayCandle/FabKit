export module fbc.setupScreen;

import fbc.coreContent;
import fbc.futil;
import fbc.relativeHitbox;
import fbc.screenSizeHitbox;
import fbc.screenManager;
import fbc.uiButton;
import fbc.uiTextButton;
import fbc.uiVerticalCanvas;
import std;

export namespace fbc {
	export class SetupScreen : public UIVerticalCanvas {
	public:
		SetupScreen(): UIVerticalCanvas(new ScreenSizeHitbox()) {
			UITextButton& b = addElement(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 130, 500, 130, 100),
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.ui_close()));
			b.setOnClick([](UIButton& i) {
				screenManager::closeCurrentScreen();
			});
		}
	};
}