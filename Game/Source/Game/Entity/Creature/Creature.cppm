module;

module fbc.Creature;

namespace fbc {
	// If a behavior is defined, the turn consists of its execution
	// Otherwise, the turn is dependent on user input
	bool Creature::act()
	{
		if (behavior) {
			behavior->act(*this);
			return true;
		}
		// TODO show stats and cards on screen
		return false;
	}

	// Reinsert a turn into queue based on current speed
	void Creature::onEndTurn()
	{
		//TODO gameState::run->getCombatInstance()->queueTurn()
	}

	// Get the actual card list associated with this pile type
	vec<uptr<Card>>& Creature::getPile(const PileType& type)
	{
		if (type == piletype::DISCARD) {
			return discardPile;
		}
		if (type == piletype::DRAW) {
			return discardPile;
		}
		if (type == piletype::EXPEND) {
			return discardPile;
		}
		return hand;
	}
}