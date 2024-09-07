export module fbc.PassiveData;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectRarity;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class PassiveData : public GameObjectData<PassiveData> {
	public:
		static constexpr cstr FOLDER = "Passives";
		static constexpr cstr LOCPATH = "PassiveStrings";

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

		PassiveData(BaseContent& source, strv id) : GameObjectData(source, id) {}
		PassiveData(BaseContent& source, strv id, const ExportFields& fields) : GameObjectData(source, id), data(fields) {}

		RuntimeFields data;
	};
}