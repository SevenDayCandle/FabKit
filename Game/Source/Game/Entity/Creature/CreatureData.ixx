export module fbc.CreatureData;

import fbc.BaseContent;
import fbc.FieldObjectData;
import fbc.FUtil;
import std;

export namespace fbc {
	export class CreatureData : FieldObjectData {
	public:
		CreatureData(BaseContent& source, strv ID): FieldObjectData(source, ID) {}
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