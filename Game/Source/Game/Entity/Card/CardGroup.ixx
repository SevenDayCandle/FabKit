export module fbc.CardGroup;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.IRegisterable;

namespace fbc {
	export class CardGroup : public IRegisterable<CardGroup> {
	public:
		CardGroup(BaseContent& source, strv id) : source(source), id(id) {}

		const BaseContent& source;
		const str id;

		operator strv() const override { return id; }
	};
}