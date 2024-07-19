export module fbc.RunEncounter;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.EncounterCreatureEntry;
import fbc.ContentRegisterable;
import std;

namespace fbc {
	export class RunEncounter : public ContentRegisterable<RunEncounter> {
	public:
		struct Data {
			bool boss = false;
			int fieldCols = 6;
			int fieldRows = 6;
			int level = 1;
			int time = 100;
			pair<str,str> zone;
			vec<pair<int, int>> startPos;
			vec<EncounterCreatureEntry> creatures;
		};

		RunEncounter(BaseContent& source, strv id, Data& data): ContentRegisterable(source, id), data(data) {}
		virtual ~RunEncounter() {}

		Data data;
	};
}