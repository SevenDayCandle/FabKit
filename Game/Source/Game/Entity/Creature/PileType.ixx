export module fbc.PileType;

import fbc.FUtil;
import fbc.KeyedItem;
import std;

namespace fbc {
	export class PileType : public KeyedItem<PileType> {
	public:
		PileType(strv key) : KeyedItem<PileType>(key) {}
	};

	export namespace piletype {

		export const PileType DISCARD("DISCARD");
		export const PileType DRAW("DRAW");
		export const PileType EXPEND("EXPEND");
		export const PileType HAND("HAND");
	}
}