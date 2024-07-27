export module fbc.Keyword;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.ContentRegisterable;
import std;

namespace fbc {
	export constexpr strv PATH_KEYWORDS = "Keywords";

	export class Keyword : public ContentRegisterable<Keyword> {
	public:
		Keyword(BaseContent& source, strv id) : ContentRegisterable(source, id) {}
	};
}