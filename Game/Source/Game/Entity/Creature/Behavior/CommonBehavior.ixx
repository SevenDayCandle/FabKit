export module fbc.RegisteredCreatureBehavior;

import fbc.Creature;
import fbc.FUtil;
import fbc.KeyedItem;
import std;

namespace fbc {
	export class CommonBehavior : public KeyedItem<CommonBehavior>, public Creature::Behavior {
	public:
		CommonBehavior(strv key): KeyedItem<CommonBehavior>(key) {}
		virtual ~CommonBehavior() {}
	};
}