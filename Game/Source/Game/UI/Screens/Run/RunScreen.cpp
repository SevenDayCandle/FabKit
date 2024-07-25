module;

module fbc.RunScreen;

namespace fbc {

	void RunScreen::open()
	{
		// TODO For testing only, remove when run starting is properly implemented
		GameRun::startRun(5);

		// Add buttons for each room in the current zone
		for (const RunRoom& room : GameRun::current->getRooms()) {
			this->addElement(makeRoomButton(const_cast<RunRoom&>(room)));
		}
	}

	// Generate a button representing a room
	uptr<UIButton> RunScreen::makeRoomButton(RunRoom& room)
	{
		uptr<UITextButton> button = make_unique<UITextButton>(new RelativeHitbox(*hb, ROOM_OFFSET + room.col * ROOM_SIZE * 2, ROOM_OFFSET + room.row * ROOM_SIZE * 2, ROOM_SIZE, ROOM_SIZE),
			cct.images.panel, cct.fontRegular(), room.type.id.substr(0, 1));
		button->setOnClick([&room](UIButton& i) {
			GameRun::current->startRoom(&room);
			room.onAfterClick();
		});
		return button;
	}
}