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
		struct Fields {
			int maxUpgrades = 0;
			ObjectRarity* rarity;
			vec<str> upgradeBranches;
		};

		PassiveData(BaseContent& source, strv id) : GameObjectDataDerived(source, id) {}
		PassiveData(BaseContent& source, strv id, const Fields& fields) : GameObjectDataDerived(source, id), data(fields) {}

		Fields data;
		vec<uptr<Effect>> effects;
	};
}