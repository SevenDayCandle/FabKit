export module fbc.EffectKeyword;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.Keyword;
import std;

namespace fbc {
	export class EffectKeyword : public Keyword {
	public:
		EffectKeyword(BaseContent& content, strv id): Keyword(content, id) {}

		vec<uptr<Effect>> effects;
	};
}