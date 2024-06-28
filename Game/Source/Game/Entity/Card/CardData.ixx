export module fbc.CardData;

import fbc.BaseContent;
import fbc.CardGroup;
import fbc.CardType;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectRarity;
import std;

namespace fbc {
	export class CardData : public GameObjectDataDerived<CardData> {
	public:
		CardData(BaseContent& source, strv id) : GameObjectDataDerived(source, id) {}
		virtual ~CardData() {}

		bool isUpgradeBranchOptional = true;
		bool targetAlly = false;
		bool targetEnemy = true;
		bool targetSquare = false;
		CardGroup* group;
		CardType* type;
		int costBase = 1;
		int costUp = 0;
		int maxCopies = -1;
		int maxUpgrades = 1;
		int targetRangeMax = 1;
		int targetRangeMaxUp = 0;
		int targetRangeMin = 1;
		int targetRangeMinUp = 0;
		int targetSizeX = 1;
		int targetSizeXUp = 0;
		int targetSizeY = 1;
		int targetSizeYUp = 0;
		ObjectRarity* rarity;
		vec<uptr<Effect>> effects;
		vec<str> tags;
		vec<str> upgradeBranches;

		inline int getCost(int level) const { return costBase + costUp * level; }
	};
}