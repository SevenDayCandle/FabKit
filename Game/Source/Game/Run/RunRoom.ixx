export module fbc.RunRoom;

import fbc.FUtil;
import fbc.GameRNG;
import fbc.KeyedItem;
import fbc.RunEncounter;
import std;

namespace fbc {
	export class RunRoom {
	public:
		class RoomType : public KeyedItem<RoomType> {
		public:
			RoomType(strv key) : KeyedItem<RoomType>(key) {}
		};

		RunRoom(RoomType& type): type(type) {}
		virtual ~RunRoom() = default;

		RoomType& type;

		RunEncounter* getEncounter(GameRNG& rng);
	};

	export namespace roomtype {
		export const RunRoom::RoomType BOSS("BOSS");
		export const RunRoom::RoomType COMBAT("COMBAT");
		export const RunRoom::RoomType ELITE("ELITE");
		export const RunRoom::RoomType EVENT("EVENT");
		export const RunRoom::RoomType REST("REST");
		export const RunRoom::RoomType SHOP("SHOP");
	}

	/* Returns any room meeting the following criteria:
	 * Eligible for the current zone (i.e. zone id matches or is common encounter and zone allows for common encounters)
	 * For boss rooms, is a boss encounter and has not been encountered yet
	 * For non-boss rooms, if level is equal to the room difficulty
	 */
	RunEncounter* RunRoom::getEncounter(GameRNG& rng)
	{
		// TODO
		return nullptr;
	}
}