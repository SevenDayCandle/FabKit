module;

import fbc.Card;
import fbc.CardData;
import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.GameRun;
import fbc.Passive;
import fbc.PassiveData;

module fbc.Creature;

namespace fbc {
	// If a behavior is defined, the turn consists of its execution
	// Otherwise, the turn is dependent on user input
	bool Creature::onTurnBegin()
	{
		drawForStartOfTurn();
		refreshValuesForStartOfTurn();

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
		queueTurn();
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
		PileGroup& sourcePile = getPile(source);
		auto it = std::ranges::find_if(sourcePile, [&card](const uptr<Card>& ptr) {
			return ptr.get() == &card;
		});

		if (it != sourcePile.end()) {
			PileGroup& destPile = getPile(dest);
			moveBetweenPiles(it, sourcePile, destPile);
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
		// if (current->getCombatInstance()->getCurrentTurn()->owner == this) do card pile animations

		return card;
	}

	// For field images, use the field override if it exists, otherwise fall back to the data
	IDrawable& Creature::getImageField() const
	{
		if (imageFieldOverride) {
			return *imageFieldOverride;
		}
		return data.getImageField();
	}

	// For portrait images, use theportrait override if it exists, otherwise fall back to the data
	IDrawable& Creature::getImagePortrait() const
	{
		if (imagePortraitOverride) {
			return *imagePortraitOverride;
		}
		return data.getImagePortrait();
	}

	// A value that determines how "quickly" this creature will onTurnBegin. The higher the value, the higher in the action queue this creature's turns will be placed
	int Creature::getActionSpeed()
	{
		int base = data.getResultActSpeed(upgrades);
		// TODO subscribers
		// TODO statuses
		return base;
	}

	// How many cards this creature draws at the start of its turn
	int Creature::getCardDraw()
	{
		int base = data.getResultHandDraw(upgrades);
		// TODO subscribers
		// TODO statuses
		return base;
	}

	// How much energy this creature gains at the start of its turn
	int Creature::getEnergyGain()
	{
		int base = data.getResultEnergyGain(upgrades);
		// TODO subscribers
		// TODO statuses
		return base;
	}

	// Get the actual card list associated with this pile type
	Creature::PileGroup& Creature::getPile(const PileType& type)
	{
		if (type == piletype::DISCARD) {
			return discardPile;
		}
		if (type == piletype::DRAW) {
			return drawPile;
		}
		if (type == piletype::EXPEND) {
			return expendPile;
		}
		return hand;
		// TODO support custom pile types
	}

	// At the start of turn, discard hand and draw new hand
	void Creature::drawForStartOfTurn()
	{
		for (PileGroup::iterator it = hand.begin(); it != hand.end(); ++it) {
			// TODO check for destination pile based on card properties
			moveBetweenPiles(it, hand, discardPile, false);
		}

		int draw = getCardDraw();
		for (PileGroup::iterator it = drawPile.begin(); it != drawPile.end() && it < drawPile.begin() + draw && hand.size() < handSize; ++it) {
			moveBetweenPiles(it, drawPile, hand, false);
		}
	}

	// Set up cards and passives for this creature
	void Creature::initialize(vec<ItemListing>& setupCards, vec<ItemListing>& setupPassives)
	{
		for (ItemListing& listing : setupCards) {
			CardData* data = CardData::get(listing.id);
			if (data) {
				drawPile.push_back(make_unique<Card>(*data, listing.upgrades));
			}
		}

		// TODO shuffle draw pile based on rng

		// TODO passives
		for (ItemListing& listing : setupPassives) {
			PassiveData* data = PassiveData::get(listing.id);
			if (data) {
				uptr<Passive> pa = make_unique<Passive>(*data, listing.upgrades);
				passives.push_back(move(pa));
			}
		}
	}

	void Creature::queueTurn()
	{
		int actionValue = DEFAULT_ROUND_LENGTH * 100 / (1 + getActionSpeed());
		GameRun::current->getCombatInstance()->queueTurn(*this, actionValue);
	}

	// Refresh energy, movement, etc. on this creature
	void Creature::refreshValuesForStartOfTurn()
	{
		energy = std::min(energy + getEnergyGain(), energyMax);
		movement = movementMax;
		// TODO visuals
		// TODO hooks
	}

	void Creature::moveBetweenPiles(Creature::PileGroup::iterator it, Creature::PileGroup& sourcePile, Creature::PileGroup& destPile, bool manual)
	{
		destPile.push_back(move(*it));
		sourcePile.erase(it);
		// TODO hand size check
		// TODO hooks only if not from play
	}
}