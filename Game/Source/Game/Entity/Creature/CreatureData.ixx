export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.GameObjectData;
import fbc.FUtil;
import std;

namespace fbc {
	export class CreatureData : public GameObjectDataDerived<CreatureData> {
	public:
		struct Fields {
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
			int movement;
			int movementUpgrade;
			str defaultBehavior;
			vec<pair<str, int>> defaultCards;
			vec<pair<str, int>> passives;
		};

		CreatureData(BaseContent& source, strv id): GameObjectDataDerived(source, id) {}
		CreatureData(BaseContent& source, strv id, const Fields& fields) : GameObjectDataDerived(source, id), data(fields) {}
		Fields data;

		inline int getResultActSpeed(int upgrade) const { return data.actSpeed + upgrade * data.actSpeedUpgrade; }
		inline int getResultEnergyGain(int upgrade) const { return data.energyGain + upgrade * data.energyGainUpgrade; }
		inline int getResultEnergyMax(int upgrade) const { return data.energyMax + upgrade * data.energyMaxUpgrade; }
		inline int getResultHandDraw(int upgrade) const { return data.handDraw + upgrade * data.handDrawUpgrade; }
		inline int getResultHandSize(int upgrade) const { return data.handSize + upgrade * data.handSizeUpgrade; }
		inline int getResultHealth(int upgrade) const { return data.health + upgrade * data.healthUpgrade; }
		inline int getResultMovement(int upgrade) const { return data.movement + upgrade * data.movementUpgrade; }
	};
}