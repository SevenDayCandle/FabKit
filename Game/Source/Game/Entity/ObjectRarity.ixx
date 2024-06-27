export module fbc.ObjectRarity;

import fbc.FUtil;
import fbc.KeyedItem;

export namespace fbc {
	export struct ObjectRarity : public KeyedItem<ObjectRarity> {
	public:
		ObjectRarity(strv key, uint32 weight = 0) : KeyedItem<ObjectRarity>(key), weight(weight) {}

		const uint32 weight;
	};

	export namespace rarity {
		export const ObjectRarity COMMON("COMMON", 1);
		export const ObjectRarity UNCOMMON("UNCOMMON", 2);
		export const ObjectRarity RARE("RARE", 3);
		export const ObjectRarity EPIC("EPIC", 4);
		export const ObjectRarity LEGENDARY("LEGENDARY", 5);
		export const ObjectRarity SPECIAL("SPECIAL", 0);
	}
}