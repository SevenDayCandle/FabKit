export module fbc.CardType;

import fbc.FUtil;
import fbc.KeyedItem;

export namespace fbc {
	export class CardType : public KeyedItem<CardType> {
	public:
		CardType(strv key) : KeyedItem<CardType>(key) {}
	};

	export namespace cardtype {
		export const CardType DAMAGE("DAMAGE");
	}
}