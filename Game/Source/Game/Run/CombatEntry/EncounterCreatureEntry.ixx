export module fbc.EncounterCreatureEntry;

import fbc.FUtil;
import std;

namespace fbc {
	export struct EncounterCreatureEntry {
		int faction;
		int posCol;
		int posRow;
		int upgrades;
		str id;
	};
}