export module fbc.RunCreatureEntry;

import fbc.CreatureData;
import fbc.FUtil;
import fbc.Hitbox;
import sdl;
import std;

export namespace fbc {
	export class RunCreatureEntry {
	public:
		RunCreatureEntry(CreatureData& data): data(data), health(data.health), cards(data.defaultCards) {}
		RunCreatureEntry(CreatureData& data, int upgrades) : data(data), health(data.getResultHealth(upgrades)), upgrades(upgrades), cards(data.defaultCards) {}
		RunCreatureEntry(const RunCreatureEntry& other) : data(other.data), health(other.health), upgrades(other.upgrades), cards(other.cards), passives(other.passives) {}
		virtual ~RunCreatureEntry() = default;

		CreatureData& data;
		int health;
		int upgrades = 0;
		vec<str> cards;
		vec<str> passives;
	};

	export class CombatRunCreatureEntry : public RunCreatureEntry {
	public:
		CombatRunCreatureEntry(CreatureData& data, int faction, int col, int row): RunCreatureEntry(data), faction(faction), posCol(col), posRow(row) {}
		CombatRunCreatureEntry(CreatureData& data, int upgrades, int faction, int col, int row) : RunCreatureEntry(data, upgrades), faction(faction), posCol(col), posRow(row) {}
		CombatRunCreatureEntry(const RunCreatureEntry& entry, int faction, int col, int row) : RunCreatureEntry(entry), faction(faction), posCol(col), posRow(row) {}

		int faction;
		int posCol;
		int posRow;
	};
}