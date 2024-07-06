export module fbc.RunEncounter;

import fbc.FUtil;
import fbc.EncounterCreatureEntry;
import fbc.ContentRegisterable;
import std;

namespace fbc {
	export class RunEncounter : public ContentRegisterable<RunEncounter> {
	public:
		struct Data {
			bool boss;
			int fieldCols;
			int fieldRows;
			int level;
			int time;
			str zone;
			vec<pair<int, int>> startPos;
			vec<EncounterCreatureEntry> inputFieldObjects;
		};

		RunEncounter(strv id, Data& data): id(id), data(data) {}
		virtual ~RunEncounter() {}

		const str id;
		Data data;

		operator strv() const override { return id; }
	};
}