export module fbc.PassiveData;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectRarity;
import sdl;
import std;

namespace fbc {
	export class PassiveData : public GameObjectDataDerived<PassiveData> {
	public:
		PassiveData(BaseContent& source, strv id) : GameObjectDataDerived(source, id) {}

		int maxUpgrades = 0;
		ObjectRarity* rarity;
		vec<uptr<Effect>> effects;
		vec<str> upgradeBranches;
	};
}