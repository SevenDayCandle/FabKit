export module fbc.SavedCreatureEntry;

import fbc.CreatureData;
import fbc.FUtil;
import std;

export namespace fbc {
	export class SavedCreatureEntry {
	public:
		SavedCreatureEntry() = default;
		SavedCreatureEntry(CreatureData& data, strv behavior, int upgrades) : id(data.id), behaviorId(behavior), health(data.getResultHealth(upgrades)), upgrades(upgrades), cards(data.data.defaultCards) {}
		SavedCreatureEntry(strv dataId, strv behavior, int upgrades) : SavedCreatureEntry(*CreatureData::get(dataId), behavior, upgrades) {}
		SavedCreatureEntry(const SavedCreatureEntry& other) : id(other.id), health(other.health), upgrades(other.upgrades), cards(other.cards), passives(other.passives) {}
		virtual ~SavedCreatureEntry() = default;

		int health;
		int upgrades = 0;
		str behaviorId;
		str id;
		vec<pair<str, int>> cards;
		vec<pair<str, int>> passives;
	};
}