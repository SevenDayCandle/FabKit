export module fbc.TitleScreen;

import fbc.CoreContent;
import fbc.FWindow;
import fbc.RunScreen;
import fbc.ScreenPosHitbox;
import fbc.ScreenSizeHitbox;
import fbc.SettingsDialog;
import fbc.UIButton;
import fbc.UIScreen;
import fbc.UITextButton;
import fbc.FUtil;
import std;

namespace fbc {
	export class TitleScreen : public UIScreen {
	public:
		TitleScreen(FWindow& window, CoreContent& cct): UIScreen(window, make_unique<ScreenSizeHitbox>(window)) {
			UITextButton& b = add(make_unique<UITextButton>(window,
				make_unique<ScreenPosHitbox>(window, 0.5f, 0.5f, 290, 170),
				cct.images.uiPanel,
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([this, &cct](UIButton& i) {
				SettingsDialog::openNew(win, cct);
				});

			UITextButton& b2 = stackYDir(std::make_unique<UITextButton>(window,
				make_unique<ScreenPosHitbox>(window, 0.5f, 0.5f, 290, 170),
				cct.images.uiPanel,
				cct.fontRegular(),
				cct.strings.screen_setup_header()));
			b2.setOnClick([this, &cct](UIButton& i) {
				win.openScreen(make_unique<RunScreen>(win, cct));
			});
		}
	};
}