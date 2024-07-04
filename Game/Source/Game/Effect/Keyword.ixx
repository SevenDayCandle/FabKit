export module fbc.Keyword;

import fbc.Effect;
import fbc.FUtil;
import fbc.IRegisterable;
import std;

namespace fbc {
	export class Keyword : public IRegisterable<Keyword> {
	public:
		Keyword(strv id): id(id) {}

		const str id;

		operator strv() const override { return id; }
	};
}