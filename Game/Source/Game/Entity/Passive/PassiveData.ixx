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
		struct ExportFields {
			int maxUpgrades;
			str effects;
			str rarity;
			vec<str> upgradeBranches;
		};

		struct RuntimeFields {
			RuntimeFields() {}
			RuntimeFields(const ExportFields& fields) {
				maxUpgrades = fields.maxUpgrades;
				rarity = ObjectRarity::get(fields.rarity);
				// TODO: Populate effects from fields.effects
				upgradeBranches = fields.upgradeBranches;
			}
			RuntimeFields(RuntimeFields&& other) = default;

			int maxUpgrades = 0;
			ObjectRarity* rarity;
			vec<str> upgradeBranches;
			vec<uptr<Effect>> effects;
		};

		PassiveData(BaseContent& source, strv id) : GameObjectDataDerived(source, id) {}
		PassiveData(BaseContent& source, strv id, const ExportFields& fields) : GameObjectDataDerived(source, id), data(fields) {}

		RuntimeFields data;
	};
}