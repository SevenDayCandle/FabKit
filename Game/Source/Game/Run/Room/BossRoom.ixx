export module fbc.BossRoom;

import fbc.FUtil;
import fbc.RunEncounter;
import fbc.RunRoom;
import fbc.RunZone;
import std;

namespace fbc {
	export class BossRoom : public RunRoom::RoomType {
	public:
		BossRoom() : RunRoom::RoomType(ID, 0) {}

		static constexpr strv ID = "BossRoom";

		virtual bool isEncounterValid(RunEncounter* encounter) {
			return encounter->data.boss;
		}
	};
}