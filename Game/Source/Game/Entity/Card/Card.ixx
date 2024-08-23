export module fbc.Card;

import fbc.CardData;
import fbc.CombatSquare;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PileType;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class Card : public GameObjectD<CardData> {
	public:
		Card(CardData& data, int upgrades = 0) : GameObjectD<CardData>(data), upgrades(upgrades) {}

		int upgrades;
		opt<vec<uptr<Effect>>> effectOverride;

		inline int cost() const { return data.getCost(upgrades); };
		inline vec<uptr<Effect>>& getEffects() { return effectOverride ? effectOverride.value() : data.data.effects; }

		bool isPlayable();
		Card& setUpgrade(int upgrades);
		const PileType& getPileAfterUse();
		
		void use(GameObject* source, CombatSquare& square);
	};
}