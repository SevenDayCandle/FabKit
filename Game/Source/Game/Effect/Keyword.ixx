export module fbc.Keyword;

import fbc.FUtil;
import fbc.Effect;
import std;

export namespace fbc {
	export class Keyword {
	public:
		Keyword(strv id): id(id) {}
		virtual ~Keyword() {}

		const str id;

		vec<uptr<Effect>> effects;
	};
}