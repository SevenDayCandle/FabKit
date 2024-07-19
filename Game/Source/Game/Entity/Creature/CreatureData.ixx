export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.GameObjectData;
import fbc.FUtil;
import fbc.ItemListing;
import std;

namespace fbc {
	export class CreatureData : public GameObjectData<CreatureData> {
	public:
		struct Fields {
			int actSpeed = 100;
			int actSpeedUpgrade = 0;
			int energyGain = 9;
			int energyGainUpgrade = 0;
			int energyMax = 9;
			int energyMaxUpgrade = 0;
			int handDraw = 5;
			int handDrawUpgrade = 0;
			int handSize = 5;
			int handSizeUpgrade = 0;
			int health = 300;
			int healthUpgrade = 30;
			int movement = 3;
			int movementUpgrade = 0;
			str defaultBehavior;
			vec<ItemListing> defaultCards;
			vec<ItemListing> passives;
		};

		CreatureData(BaseContent& source, strv id): GameObjectData(source, id) {}
		CreatureData(BaseContent& source, strv id, const Fields& fields) : GameObjectData(source, id), data(fields) {}
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