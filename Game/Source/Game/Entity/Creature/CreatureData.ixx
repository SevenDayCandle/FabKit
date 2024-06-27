export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.GameObjectData;
import fbc.FUtil;
import std;

export namespace fbc {
	export class CreatureData : public GameObjectDataDerived<CreatureData> {
	public:
		CreatureData(BaseContent& source, strv id): GameObjectDataDerived(source, id) {}
		virtual ~CreatureData() {}

		int actSpeed;
		int actSpeedUpgrade;
		int draw;
		int drawUpgrade;
		int energy;
		int energyUpgrade;
		int health;
		int healthUpgrade;
		int move;
		int moveUpgrade;
		vec<str> defaultCards;
	};
}