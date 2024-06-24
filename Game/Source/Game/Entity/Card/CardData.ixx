export module fbc.CardData;

import fbc.BaseContent;
import fbc.CardGroup;
import fbc.CardType;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectRarity;
import std;

export namespace fbc {
	export class CardData : GameObjectData {
	public:
		CardData(BaseContent& source, strv ID) : GameObjectData(source, ID) {}
		virtual ~CardData() {}

		bool isUpgradeBranchOptional;
		bool targetAlly;
		bool targetEnemy;
		bool targetSquare;
		CardGroup* group;
		CardType* type;
		int costBase;
		int costUp;
		int maxUpgrades = 1;
		int targetRange;
		int targetRangeUp;
		int targetSizeX;
		int targetSizeXUp;
		int targetSizeY;
		int targetSizeYUp;
		ObjectRarity* rarity;
		vec<uptr<Effect>> effects;
		vec<str> upgradeBranches;

		inline int getCost(int level) { return costBase + costUp * level; }
	};
}