export module fbc.GameRun;

import fbc.CombatInstance;
import fbc.FUtil;
import fbc.GameRNG;
import fbc.RunEncounter;
import fbc.RunRoom;
import fbc.RunZone;
import fbc.SavedCreatureEntry;
import std;

// TODO save data
namespace fbc {
	export class GameRun {
	public:
		struct SaveData {
			int faction;
			int posCol;
			int posRow;
			int rngCard;
			int rngEncounter;
			int rngMap;
			int rngReward;
			unsigned int seed;
			pair<str, str> currentZone;
			set<str> encounteredZones;
			vec<SavedCreatureEntry> creatures;
		};

		GameRun(int seed): seed(seed) {
			initialize();
		}
		GameRun(SaveData& save): GameRun(save.seed) {
			loadFromSave(save);
		}

		GameRNG rngCard;
		GameRNG rngEncounter;
		GameRNG rngMap;
		GameRNG rngReward;
		int faction = 0;
		vec<SavedCreatureEntry> creatures;

		static uptr<GameRun> current;

		inline CombatInstance* getCombatInstance() const { return combatInstance.get(); }
		inline ref_view<const vec<RunRoom>> getRooms() const { return std::views::all(rooms); }
		inline ref_view<vec<RunRoom>> getRooms() { return std::views::all(rooms); }
		inline RunRoom* getCurrentRoom() const { return currentRoom; }
		inline RunZone* getCurrentZone() const { return currentZone; }
		inline unsigned int getSeed() const { return seed; }

		RunRoom* getRoomAt(int col, int row);
		RunZone* getValidZone();
		SaveData generateSave();
		void initialize();
		void loadFromSave(SaveData& save);
		void startCombat();
		void startCombat(RunEncounter* encounter);
		void startRoom(RunRoom* room);
		void startZone(RunZone* zone);

		static void loadRun(SaveData& save);
		static void startRun(int seed);
	private:
		int lastRngMap;
		int posCol;
		int posRow;
		unsigned int seed;
		RunRoom* currentRoom;
		RunZone* currentZone;
		set<str> encounteredZones;
		uptr<CombatInstance> combatInstance;
		vec<RunRoom> rooms;
	};

	uptr<GameRun> GameRun::current = nullptr;
}