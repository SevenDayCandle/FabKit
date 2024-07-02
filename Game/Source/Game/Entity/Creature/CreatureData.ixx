export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.GameObjectData;
import fbc.FUtil;
import std;

namespace fbc {
	export class CreatureData : public GameObjectDataDerived<CreatureData> {
	public:
		CreatureData(BaseContent& source, strv id): GameObjectDataDerived(source, id) {}

		int actSpeed;
		int actSpeedUpgrade;
		int energyGain;
		int energyGainUpgrade;
		int energyMax;
		int energyMaxUpgrade;
		int handDraw;
		int handDrawUpgrade;
		int handSize;
		int handSizeUpgrade;
		int health;
		int healthUpgrade;
		int move;
		int moveUpgrade;
		vec<str> defaultCards;
		vec<str> passives;

		inline int getResultActSpeed(int upgrade) const { return actSpeed + upgrade * actSpeedUpgrade; }
		inline int getResultEnergyGain(int upgrade) const { return energyGain + upgrade * energyGainUpgrade; }
		inline int getResultEnergyMax(int upgrade) const { return energyMax + upgrade * energyMaxUpgrade; }
		inline int getResultHandDraw(int upgrade) const { return handDraw + upgrade * handDrawUpgrade; }
		inline int getResultHandSize(int upgrade) const { return handSize + upgrade * handSizeUpgrade; }
		inline int getResultHealth(int upgrade) const { return health + upgrade * healthUpgrade; }
		inline int getResultMove(int upgrade) const { return move + upgrade * moveUpgrade; }
	};
}