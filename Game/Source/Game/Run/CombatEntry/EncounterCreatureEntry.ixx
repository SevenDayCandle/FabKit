export module fbc.EncounterCreatureEntry;

import fbc.FUtil;
import std;

namespace fbc {
	export struct EncounterCreatureEntry {
		int faction = 1;
		int posCol;
		int posRow;
		int upgrades = 0;
		str content;
		str id;
	};
}