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
		static const GreedyBehavior instance;

		void act(Creature& source) override;
	};

	const GreedyBehavior GreedyBehavior::instance = GreedyBehavior();

	void GreedyBehavior::act(Creature& source)
	{
		// TODO implement
	}
}