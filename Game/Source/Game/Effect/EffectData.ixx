export module fbc.EffectData;

import fbc.BaseContent;
import fbc.FUtil;
import std;

export namespace fbc {
	export class EffectData {
	public:
		EffectData(BaseContent& source, strv ID) : source(source), ID(ID) {}
		virtual ~EffectData() {}

		const BaseContent& source;
		const str ID;
	};
}