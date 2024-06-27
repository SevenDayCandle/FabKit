export module fbc.Card;

import fbc.CardData;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import sdl;
import std;

export namespace fbc {
	export class Card : public GameObjectDerived<CardData> {
	public:
		Card(CardData& data) : GameObjectDerived<CardData>(data) {}
		virtual ~Card() {}

		int upgrades;
		opt<vec<uptr<Effect>>> effectOverride;

		bool isPlayable();
		Card& setUpgrade(int upgrades);
		int cost();
		vec<uptr<Effect>>& getEffects();
		void use(GameObject* target);
	};
}