export module fbc.GreedyBehavior;

import fbc.Creature;
import fbc.FUtil;
import fbc.KeyedItem;
import std;

namespace fbc {
	export class GreedyBehavior : public Creature::Behavior {
	public:
		GreedyBehavior(): Behavior(ID) {}

		static constexpr strv ID = "GreedyBehavior";

		void act(Creature& source) override;
	};

	export const GreedyBehavior instance;


	void GreedyBehavior::act(Creature& source)
	{
		// TODO implement
	}
}