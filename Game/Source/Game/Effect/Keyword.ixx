export module fbc.Keyword;

import fbc.FUtil;
import fbc.Effect;
import std;

export namespace fbc {
	export class Keyword {
	public:
		Keyword(strv ID): ID(ID) {}
		virtual ~Keyword() {}

		const str ID;

		vec<uptr<Effect>> effects;
	};
}