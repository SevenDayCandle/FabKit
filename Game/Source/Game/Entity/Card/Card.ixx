export module fbc.Card;

import fbc.CardData;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import sdl;
import std;

namespace fbc {
	export class Card : public GameObjectDerived<CardData> {
	public:
		Card(CardData& data) : GameObjectDerived<CardData>(data) {}
		virtual ~Card() {}

		int upgrades;
		opt<vec<uptr<Effect>>> effectOverride;

		inline int cost() const { return data.costBase + data.costUp * upgrades; };
		inline vec<uptr<Effect>>& getEffects() { return effectOverride ? effectOverride.value() : data.effects; }

		bool isPlayable();
		Card& setUpgrade(int upgrades);
		
		void use(GameObject* source, int location);
	};
}