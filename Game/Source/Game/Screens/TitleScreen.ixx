export module fbc.titleScreen;

import fbc.coreContent;
import fbc.screenPosHitbox;
import fbc.screenSizeHitbox;
import fbc.screenManager;
import fbc.setupScreen;
import fbc.uiButton;
import fbc.uiCanvas;
import fbc.uiTextButton;
import fbc.futil;
import std;

export namespace fbc {
	export class TitleScreen : public UICanvas {
	public:
		TitleScreen(): UICanvas(new ScreenSizeHitbox()) {
			UITextButton& b = addElement(std::make_unique<UITextButton>(
				new ScreenPosHitbox(0.5f, 0.5f, 290, 170),
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([](UIButton& i) {
				screenManager::openScreen(std::make_unique<SetupScreen>());
				});
		}
	};
}