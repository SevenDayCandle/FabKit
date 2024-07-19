export module fbc.EffectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.ContentRegisterable;
import std;

namespace fbc {
	export class EffectData : public ContentRegisterable<EffectData> {
	public:
		EffectData(BaseContent& source, strv id) : ContentRegisterable(source, id) {}
	};
}