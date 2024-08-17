export module fbc.RunScreen;

import fbc.CoreContent;
import fbc.FWindow;
import fbc.GameRun;
import fbc.RelativeHitbox;
import fbc.RunRoom;
import fbc.SettingsDialog;
import fbc.UIButton;
import fbc.UIScreen;
import fbc.UITextButton;
import fbc.FUtil;
import std;

namespace fbc {
	constexpr float TILE_OFFSET = 300;
	constexpr float ROOM_SIZE = 128;

	export class RunScreen : public UIScreen {
	public:
		RunScreen(FWindow& win): UIScreen(win) {}

		void open() override;
	private:
		uptr<UIButton> makeRoomButton(RunRoom& room);
	};
}