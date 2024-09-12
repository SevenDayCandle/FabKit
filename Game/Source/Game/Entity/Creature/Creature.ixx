export module fbc.Creature;

import fbc.AttributeObject;
import fbc.Card;
import fbc.CombatSquare;
import fbc.CreatureData;
import fbc.FUtil;
import fbc.GameObject;
import fbc.KeyedItem;
import fbc.IDrawable;
import fbc.ItemListing;
import fbc.PileType;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class Creature : public GameObjectD<CreatureData>, public CombatSquare::OccupantObject {
	public:
		class Behavior : public KeyedItem<Behavior> {
		public:
			Behavior(strv key) : KeyedItem<Behavior>(key) {}

			virtual void act(Creature& source) = 0;
		};
		class PileGroup : public vec<uptr<Card>> {
		public:
			PileGroup(const PileType& type) : vec<uptr<Card>>(), type(type) {}

			const PileType& type;

			int getPosition(const Card* card);
		};

		Creature(CreatureData& data, Behavior* behavior, int faction, int upgrades, int startingHealth) :
			GameObjectD(data), behavior(behavior), faction(faction), upgrades(upgrades), health(startingHealth), energyMax(data.getResultEnergyMax(upgrades)), handSize(data.getResultHandSize(upgrades)), healthMax(data.getResultHealth(upgrades)), movementMax(data.getResultMovement(upgrades)) {
			// TODO create cards
		}
		Creature(CreatureData& data, Behavior* behavior, int faction, int upgrades) : Creature(data, behavior, faction, upgrades, data.getResultHealth(upgrades)) {}

		Behavior* behavior;
		IDrawable* imageFieldOverride;
		IDrawable* imagePortraitOverride;
		int energy;
		int energyMax;
		int faction;
		int handSize;
		int health;
		int healthMax;
		int movement;
		int movementMax;
		int upgrades;

		inline int getCardPosition(Card* card, const PileType& type) { return getPile(type).getPosition(card); }
		inline PileGroup& getHand() { return hand; }
		inline void shufflePile(const PileType& type) { shufflePile(getPile(type)); }

		virtual bool onTurnBegin() override;
		virtual void onTurnEnd() override;
		bool moveTo(CombatSquare& square);
		Card& addCardToPile(uptr<Card>&& card, const PileType& type); // TODO refactor to use conditions, refactor into action
		Card& cardFromToPile(Card& card, const PileType& source, const PileType& dest); // TODO refactor to use conditions, refactor into action
		Card& useCard(Card& card, CombatSquare& square);
		IDrawable& getImageField() const final override;
		IDrawable& getImagePortrait() const final override;
		int getActionSpeed();
		int getCardDraw();
		int getEnergyGain();
		int getMovement() override;
		PileGroup& getPile(const PileType& type);
		void drawCard();
		void drawForStartOfTurn();
		void initialize(vec<ItemListing>& cards, vec<ItemListing>& passives);
		void queueTurn() override;
		void refreshValuesForStartOfTurn();
		void reshuffleDrawPile();
		void shufflePile(PileGroup& group);
	private:
		PileGroup discardPile = PileGroup(piletype::DISCARD);
		PileGroup drawPile = PileGroup(piletype::DRAW);
		PileGroup expendPile = PileGroup(piletype::EXPEND);
		PileGroup hand = PileGroup(piletype::HAND);
		vec<uptr<AttributeObject>> passives;

		void moveBetweenPiles(PileGroup::iterator cardIt, PileGroup& sourcePile, PileGroup& destPile, bool manual = true);
	};

	int fbc::Creature::PileGroup::getPosition(const Card* card) {
		int i = 0;
		for (uptr<Card>& entry : *this) {
			if (entry.get() == card) {
				return i;
			}
			++i;
		}
		return -1;
	}
}