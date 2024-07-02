export module fbc.Creature;

import fbc.Card;
import fbc.CombatSquare;
import fbc.CreatureData;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PileType;
import fbc.RunCreatureEntry;
import sdl;
import std;

namespace fbc {
	export class Creature : public GameObjectDerived<CreatureData>, public FieldObject {
	public:
		class Behavior {
		public:
			Behavior()  {}
			virtual ~Behavior() = default;

			virtual void act(Creature& source) = 0;
		};

		Creature(CreatureData& data, int upgrades, int startingHealth, vec<str>& cards, vec<str>& passives) :
			GameObjectDerived(data), upgrades(upgrades), health(startingHealth), energyMax(data.getResultEnergyMax(upgrades)), handSize(data.getResultHandSize(upgrades)), healthMax(data.getResultHealth(upgrades)), movementMax(data.getResultMove(upgrades)) {
			// TODO create cards
		}
		Creature(CreatureData& data, int upgrades) : Creature(data, upgrades, data.getResultHealth(upgrades), data.defaultCards, data.passives) {}
		Creature(RunCreatureEntry& entry) : Creature(entry.data, entry.upgrades, entry.health, entry.cards, entry.passives) {}

		Creature::Behavior* behavior;
		int energy;
		int energyMax;
		int faction;
		int handSize;
		int health;
		int healthMax;
		int movement;
		int movementMax;
		int upgrades;

		virtual bool onTurnBegin() override;
		virtual void onTurnEnd() override;
		bool moveTo(CombatSquare& square);
		Card& cardFromToPile(Card& card, const PileType& source, const PileType& dest);
		Card& cardToPile(uptr<Card>&& card, const PileType& type);
		Card& useCard(Card& card, CombatSquare& square);
		int getActionSpeed();
		int getCardDraw();
		vec<uptr<Card>>& getPile(const PileType& type);
	private:
		CombatSquare* currentSquare;
		vec<uptr<Card>> discardPile;
		vec<uptr<Card>> drawPile;
		vec<uptr<Card>> expend;
		vec<uptr<Card>> hand;
	};
}