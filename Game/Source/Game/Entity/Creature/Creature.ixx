export module fbc.Creature;

import fbc.Card;
import fbc.CreatureBehavior;
import fbc.CreatureData;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PileType;
import sdl;
import std;

export namespace fbc {
	export class Creature : public GameObjectDerived<CreatureData>, public FieldObject {
	public:
		Creature(CreatureData& data): GameObjectDerived(data) {}
		virtual ~Creature() {}

		CreatureBehavior* behavior;
		int energy;
		int energyMax;
		int faction;
		int health;
		int healthMax;
		int movement;
		int movementMax;
		vec<uptr<Card>> discardPile;
		vec<uptr<Card>> drawPile;
		vec<uptr<Card>> expend;
		vec<uptr<Card>> hand;

		virtual void act();
		void getPile(PileType& type);
	};
}