export module fbc.RunScreen;

import fbc.CoreContent;
import fbc.GameRun;
import fbc.RelativeHitbox;
import fbc.RunRoom;
import fbc.ScreenPosHitbox;
import fbc.ScreenSizeHitbox;
import fbc.ScreenManager;
import fbc.SettingsDialog;
import fbc.UIButton;
import fbc.UITextButton;
import fbc.UIScreen;
import fbc.UITextButton;
import fbc.FUtil;
import std;

namespace fbc {
	constexpr float ROOM_OFFSET = 300;
	constexpr float ROOM_SIZE = 128;

	export class RunScreen : public UIScreen {
	public:
		RunScreen(): UIScreen(new ScreenSizeHitbox()) {}

		void open() override;
	private:
		uptr<UIButton> makeRoomButton(RunRoom& room);
	};


	void RunScreen::open()
	{
		// TODO For testing only, remove when run starting is properly implemented
		GameRun::startRun(5);

		// Add buttons for each room in the current zone
		for (const RunRoom& room : GameRun::current->getRooms()) {
			this->addElement(makeRoomButton(const_cast<RunRoom&>(room)));
		}
	}

	uptr<UIButton> RunScreen::makeRoomButton(RunRoom& room)
	{
		uptr<UITextButton> button = make_unique<UITextButton>(new RelativeHitbox(*hb, ROOM_OFFSET + room.col * ROOM_SIZE * 2, ROOM_OFFSET + room.row * ROOM_SIZE * 2, ROOM_SIZE, ROOM_SIZE),
			cct.images.panel, cct.fontRegular(), room.type.id.substr(0, 1));
		button->setOnClick([&room](UIButton& i) {GameRun::current->startRoom(&room); });
		return button;
	}
}