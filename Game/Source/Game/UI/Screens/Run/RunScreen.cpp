module;

import fbc.CombatRoom;
import fbc.CombatScreen;
import fbc.SavedCreatureEntry;

module fbc.RunScreen;

namespace fbc {

	void RunScreen::open()
	{
		// TODO For testing only, remove when run starting is properly implemented
		vec<SavedCreatureEntry> entries = {
			SavedCreatureEntry("test", "TestPlayer", "", 0) };
		GameRun::StartData data{ 0, entries };
		GameRun::startRun(5, data);


		// Add buttons for each room in the current zone
		for (const RunRoom& room : GameRun::current->getRooms()) {
			this->add(makeRoomButton(const_cast<RunRoom&>(room)));
		}
	}

	// Generate a button representing a room
	uptr<UIButton> RunScreen::makeRoomButton(RunRoom& room)
	{
		uptr<UITextButton> button = create<UITextButton>(
			relhb(TILE_OFFSET + room.col * ROOM_SIZE * 2, TILE_OFFSET + room.row * ROOM_SIZE * 2, ROOM_SIZE, ROOM_SIZE),
			cct.images.uiPanel, cct.fontRegular(), room.type.id.substr(0, 1));
		button->setOnClick([this, &room](UIButton& i) {
			GameRun::current->startRoom(&room);
			onRoomClick(room);
		});
		return button;
	}

	void RunScreen::onRoomClick(RunRoom& room) {
		if (room.type.id == CombatRoom::ID) {
			if (GameRun::current->getCombatInstance() != nullptr) {
				win.openScreen(make_unique<CombatScreen>(win, cct));
			}
		}
	}
}