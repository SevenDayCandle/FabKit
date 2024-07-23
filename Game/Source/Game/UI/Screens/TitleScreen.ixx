export module fbc.TitleScreen;

import fbc.CoreContent;
import fbc.RunScreen;
import fbc.ScreenPosHitbox;
import fbc.ScreenSizeHitbox;
import fbc.ScreenManager;
import fbc.SettingsDialog;
import fbc.UIButton;
import fbc.UIScreen;
import fbc.UITextButton;
import fbc.FUtil;
import std;

namespace fbc {
	export class TitleScreen : public UIScreen {
	public:
		TitleScreen(): UIScreen(new ScreenSizeHitbox()) {
			UITextButton& b = addElement(std::make_unique<UITextButton>(
				new ScreenPosHitbox(0.5f, 0.5f, 290, 170),
				cct.images.panel,
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([](UIButton& i) {
				SettingsDialog::openNew();
				});

			UITextButton& b2 = stackElementYDir(std::make_unique<UITextButton>(
				new ScreenPosHitbox(0.5f, 0.5f, 290, 170),
				cct.images.panel,
				cct.fontRegular(),
				cct.strings.screen_setup_header()));
			b2.setOnClick([](UIButton& i) {
				screenManager::openScreen(make_unique<RunScreen>());
			});
		}
	};
}