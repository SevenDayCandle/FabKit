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
		TitleScreen(FWindow& win): UIScreen(win, new ScreenSizeHitbox(win)) {
			UITextButton& b = add(std::make_unique<UITextButton>(win,
				new ScreenPosHitbox(win, 0.5f, 0.5f, 290, 170),
				cct.images.uiPanel,
				cct.fontRegular(),
				cct.strings.screen_title_header()));
			b.setOnClick([this](UIButton& i) {
				SettingsDialog::openNew(this->win);
				});

			UITextButton& b2 = stackYDir(std::make_unique<UITextButton>(win,
				new ScreenPosHitbox(win, 0.5f, 0.5f, 290, 170),
				cct.images.uiPanel,
				cct.fontRegular(),
				cct.strings.screen_setup_header()));
			b2.setOnClick([this](UIButton& i) {
				this->win.openScreen(make_unique<RunScreen>(this->win));
			});
		}
	};
}