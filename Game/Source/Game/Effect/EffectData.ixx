export module fbc.EffectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.IRegisterable;
import std;

namespace fbc {
	export class EffectData : public IRegisterable<EffectData> {
	public:
		EffectData(BaseContent& source, strv id) : source(source), id(id) {}

		const BaseContent& source;
		const str id;

		operator strv() const override { return id; }
	};
}