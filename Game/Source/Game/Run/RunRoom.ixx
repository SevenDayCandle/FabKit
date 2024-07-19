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

		RunRoom(RoomType& type): type(type) {}
		virtual ~RunRoom() = default;

		RoomType& type;

		inline void onEnter() { type.onEnter(); };

		RunEncounter* getEncounter(RunZone& zone, GameRNG& rng);
	};

	/* Returns any room meeting the following criteria:
	 * Eligible for the current zone (i.e. zone id matches or is common encounter and zone allows for common encounters)
	 * Has not been encountered yet in the run (TODO)
	 * Eligible in the current room type (room specific implementations)
	 */
	RunEncounter* RunRoom::getEncounter(RunZone& zone, GameRNG& rng)
	{
		pair<str, str> toPair = zone.toPair();
		vec<RunEncounter*> encounters = RunEncounter::findAllAsList([toPair, this](RunEncounter* encounter) {return encounter && encounter->data.zone == toPair && type.isEncounterValid(encounter); });
		if (encounters.size() > 0) {
			int index = rng.random(0, encounters.size() - 1);
			return encounters[index];
		}
		return nullptr;
	}
}