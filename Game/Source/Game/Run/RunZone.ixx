export module fbc.RunZone;

import fbc.BaseContent;
import fbc.ContentRegisterable;
import fbc.FUtil;
import std;

namespace fbc {
	export class RunZone : public ContentRegisterable<RunZone> {
	public:
		struct Data {
			int sizeCols = 5;
			int sizeRows = 8;
			umap<str, int> roomWeights;
			vec<int> levels;
		};
		RunZone(BaseContent& source, strv id, Data& data) : ContentRegisterable(source, id), data(data) {}
		virtual ~RunZone() = default;

		Data data;
	};
}