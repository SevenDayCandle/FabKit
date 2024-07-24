export module fbc.EncounterCreatureEntry;

import fbc.FUtil;
import std;

namespace fbc {
	export struct EncounterCreatureEntry {
		int faction = 1;
		int posCol = -1;
		int posRow = -1;
		int upgrades = 0;
		str id;
	};
}