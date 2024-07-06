export module fbc.Keyword;

import fbc.Effect;
import fbc.FUtil;
import fbc.ContentRegisterable;
import std;

namespace fbc {
	export class Keyword : public ContentRegisterable<Keyword> {
	public:
		Keyword(strv id): id(id) {}

		const str id;

		operator strv() const override { return id; }
	};
}