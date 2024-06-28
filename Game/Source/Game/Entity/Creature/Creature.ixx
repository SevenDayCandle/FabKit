export module fbc.Creature;

import fbc.Card;
import fbc.CreatureData;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PileType;
import sdl;
import std;

namespace fbc {
	export class Creature : public GameObjectDerived<CreatureData>, public FieldObject {
	public:
		class Behavior {
		public:
			Behavior()  {}
			virtual ~Behavior() {}

			virtual void act(Creature& source) = 0;
		};

		Creature(CreatureData& data) : GameObjectDerived(data) {}
		virtual ~Creature() {}

		Creature::Behavior* behavior;
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

		virtual bool act() override;
		virtual void onEndTurn() override;
		vec<uptr<Card>>& getPile(const PileType& type);
	};
}