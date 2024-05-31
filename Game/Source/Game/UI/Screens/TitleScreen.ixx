export module fbc.TitleScreen;

import fbc.CoreContent;
import fbc.ScreenPosHitbox;
import fbc.ScreenSizeHitbox;
import fbc.ScreenManager;
import fbc.SettingsDialog;
import fbc.SetupScreen;
import fbc.UIButton;
import fbc.UICanvas;
import fbc.UITextButton;
import fbc.FUtil;
import std;

export namespace fbc {
	export class TitleScreen : public UICanvas {
	public:
		TitleScreen(): UICanvas(new ScreenSizeHitbox()) {
			UITextButton& b = addElement(std::make_unique<UITextButton>(
				new ScreenPosHitbox(0.5f, 0.5f, 290, 170),
				cct.images.panel,
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([](UIButton& i) {
				SettingsDialog::openNew();
				//screenManager::openScreen(std::make_unique<SetupScreen>());
				});
		}
	};
}