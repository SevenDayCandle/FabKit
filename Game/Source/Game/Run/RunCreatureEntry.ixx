export module fbc.RunCreatureEntry;

import fbc.CreatureData;
import fbc.FUtil;
import fbc.Hitbox;
import sdl;
import std;

export namespace fbc {
	export class RunCreatureEntry {
	public:
		RunCreatureEntry(CreatureData& data, strv behavior, int upgrades) : dataId(data.id), behaviorId(behavior), health(data.getResultHealth(upgrades)), upgrades(upgrades), cards(data.data.defaultCards) {}
		RunCreatureEntry(strv dataId, strv behavior, int upgrades) : RunCreatureEntry(*CreatureData::get(dataId), behavior, upgrades) {}
		RunCreatureEntry(const RunCreatureEntry& other) : dataId(other.dataId), health(other.health), upgrades(other.upgrades), cards(other.cards), passives(other.passives) {}
		virtual ~RunCreatureEntry() = default;

		int health;
		int upgrades = 0;
		str behaviorId;
		str dataId;
		vec<pair<str, int>> cards;
		vec<pair<str, int>> passives;
	};

	export class CombatRunCreatureEntry : public RunCreatureEntry {
	public:
		CombatRunCreatureEntry(CreatureData& data, strv behavior, int upgrades, int faction, int col, int row) : RunCreatureEntry(data, behavior, upgrades), faction(faction), posCol(col), posRow(row) {}
		CombatRunCreatureEntry(strv dataId, strv behavior, int upgrades, int faction, int col, int row) : RunCreatureEntry(dataId, behavior, upgrades), faction(faction), posCol(col), posRow(row) {}
		CombatRunCreatureEntry(const RunCreatureEntry& entry, int faction, int col, int row) : RunCreatureEntry(entry), faction(faction), posCol(col), posRow(row) {}

		int faction;
		int posCol;
		int posRow;
	};
}