export module fbc.EventRoom;

import fbc.FUtil;
import fbc.GameRun;
import fbc.RunRoom;
import fbc.RunZone;
import std;

namespace fbc {
	export class EventRoom : public RunRoom::RoomType {
	public:
		EventRoom() : RunRoom::RoomType(ID, 25) {}

		static constexpr strv ID = "EventRoom";
		static const EventRoom instance;
	};

	const EventRoom EventRoom::instance = EventRoom();
}