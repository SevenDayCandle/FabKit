export module fbc.RunRoom;

import fbc.FUtil;
import fbc.GameRNG;
import fbc.KeyedItem;
import fbc.RunEncounter;
import fbc.RunZone;
import std;

namespace fbc {
	export class RunRoom {
	public:
		class RoomType : public KeyedItem<RoomType> {
		public:
			RoomType(strv key, int rate, bool allowRepeat = true) : KeyedItem<RoomType>(key), rate(rate), allowRepeat(allowRepeat) {}

			const bool allowRepeat;
			const int rate;


			virtual bool isEncounterValid(RunEncounter* encounter) { return true; }
			virtual void onEnter() {}
		};

		RunRoom(RoomType& type, int col, int row): type(type), col(col), row(row) {}
		virtual ~RunRoom() = default;

		int col;
		int row;
		RoomType& type;

		inline void onEnter() { type.onEnter(); };

		RunEncounter* getEncounter(RunZone& zone, GameRNG& rng);
	};

	/* Returns any room meeting the following criteria:
	 * Eligible for the current zone (i.e. zone id matches or is common encounter (empty zone) and zone allows for common encounters)
	 * Has not been encountered yet in the run (TODO)
	 * Eligible in the current room type (room specific implementations)
	 */
	RunEncounter* RunRoom::getEncounter(RunZone& zone, GameRNG& rng)
	{
		str id = zone.toString();
		vec<RunEncounter*> encounters = RunEncounter::findAllAsList([&zone, &id, this](RunEncounter* encounter) {
			return encounter && (encounter->data.zone == id || (zone.data.allowCommonEncounters && encounter->data.zone.empty())) && type.isEncounterValid(encounter);
		});
		if (encounters.size() > 0) {
			int index = rng.random(0, encounters.size() - 1);
			return encounters[index];
		}
		return nullptr;
	}
}