module;

import fbc.CombatInstance;
import fbc.GameRun;

module fbc.Creature;

namespace fbc {
	// If a behavior is defined, the turn consists of its execution
	// Otherwise, the turn is dependent on user input
	bool Creature::onTurnBegin()
	{
		// TODO draw cards from deck
		// TODO energy, etc. value setup
		// TODO start turn hooks
		// TODO status updates
		if (behavior) {
			behavior->act(*this);
			return true;
		}
		// TODO show stats and cards on screen
		return false;
	}

	// Reinsert a turn into queue based on current speed
	void Creature::onTurnEnd()
	{
		int actionValue = DEFAULT_ROUND_LENGTH * 100 / (1 + getActionSpeed());
		currentRun->getCombatInstance()->queueTurn(*this, actionValue);
		// TODO end turn hooks
		// TODO status updates
	}

	// Attempt to move to the designated square. Return true if successful
	bool Creature::moveTo(CombatSquare& square)
	{
		// TODO hooks for movement amount
		int cost = 1;
		if (movement < cost) {
			return false;
		}
		if (currentSquare) {
			currentSquare->setOccupant(nullptr);
		}
		square.setOccupant(this);

		return true;
	}

	// Move a card from one pile to another, returning the moved card
	Card& Creature::cardFromToPile(Card& card, const PileType& source, const PileType& dest)
	{
		vec<uptr<Card>>& sourcePile = getPile(source);
		auto it = std::ranges::find_if(sourcePile, [&card](const uptr<Card>& ptr) {
			return ptr.get() == &card;
		});

		if (it != sourcePile.end()) {
			vec<uptr<Card>>& destPile = getPile(dest);
			destPile.push_back(move(*it));
			sourcePile.erase(it);
			// TODO hooks only if not from play
		}
		return card;
	}

	// Add a card to a pile, returning the resulting card
	Card& Creature::cardToPile(uptr<Card>&& card, const PileType& type)
	{
		Card& ref = *card;
		vec<uptr<Card>>& pile = getPile(type);
		pile.push_back(move(card));
		// TODO hooks
		return ref;
	}

	// Play a card from this creature's hand, and then move the played card to the designated pile if that card was in the hand or draw pile
	Card& Creature::useCard(Card& card, CombatSquare& square)
	{
		card.use(this, square);

		const PileType& dest = card.getPileAfterUse();
		vec<uptr<Card>>& destPile = getPile(dest);

		auto it = std::ranges::find_if(hand, [&card](const uptr<Card>& ptr) {
			return ptr.get() == &card;
		});
		if (it == hand.end()) {
			destPile.push_back(move(*it));
			hand.erase(it);
		}
		else {
			it = std::ranges::find_if(drawPile, [&card](const uptr<Card>& ptr) {
				return ptr.get() == &card;
				});
			if (it == drawPile.end()) {
				destPile.push_back(move(*it));
				hand.erase(it);
			}
		}

		// TODO graphical updates
		// if (currentRun->getCombatInstance()->getCurrentTurn()->owner == this) do card pile animations

		return card;
	}

	// A value that determines how "quickly" this creature will onTurnBegin. The higher the value, the higher in the action queue this creature's turns will be placed
	int Creature::getActionSpeed()
	{
		int base = data.actSpeed + data.actSpeedUpgrade * upgrades;
		// TODO subscribers
		// TODO statuses
		return base;
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
		// TODO support custom pile types
	}
}