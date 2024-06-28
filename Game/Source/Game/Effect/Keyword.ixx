export module fbc.Keyword;

import fbc.Effect;
import fbc.FUtil;
import fbc.IRegisterable;
import std;

namespace fbc {
	export class Keyword : public IRegisterable<Keyword> {
	public:
		Keyword(strv id): id(id) {}
		virtual ~Keyword() {}

		const str id;

		inline strv registrationID() const override { return id; }
	};
}