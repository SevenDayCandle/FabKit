export module fbc.CardGroup;

import fbc.FUtil;
import fbc.KeyedItem;

export namespace fbc {
	export class CardGroup : KeyedItem<CardGroup> {
	public:
		CardGroup(strv key) : KeyedItem<CardGroup>(key) {}
	};
}