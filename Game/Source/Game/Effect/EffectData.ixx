export module fbc.EffectData;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.IRegisterable;
import std;

namespace fbc {
	export class EffectData : public IRegisterable<EffectData> {
	public:
		EffectData(BaseContent& source, strv id) : source(source), id(id) {}
		virtual ~EffectData() {}

		const BaseContent& source;
		const str id;

		inline strv registrationID() const override { return id; }
	};
}