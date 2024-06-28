export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.GameObjectData;
import fbc.FUtil;
import std;

namespace fbc {
	export class CreatureData : public GameObjectDataDerived<CreatureData> {
	public:
		CreatureData(BaseContent& source, strv id): GameObjectDataDerived(source, id) {}
		virtual ~CreatureData() {}

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
	};
}