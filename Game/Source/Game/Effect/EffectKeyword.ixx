export module fbc.EffectKeyword;

import fbc.Effect;
import fbc.FUtil;
import fbc.Keyword;
import std;

namespace fbc {
	export class EffectKeyword : public Keyword {
	public:
		EffectKeyword(strv id): Keyword(id) {}

		vec<uptr<Effect>> effects;
	};
}