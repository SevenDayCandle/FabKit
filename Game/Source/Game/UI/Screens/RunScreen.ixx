export module fbc.RunScreen;

import fbc.CoreContent;
import fbc.GameRun;
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
	export class RunScreen : public UIScreen {
	public:
		RunScreen(): UIScreen(new ScreenSizeHitbox()) {}

		void open() override;
	};


	void RunScreen::open()
	{
		GameRun::startRun(5);
	}
}