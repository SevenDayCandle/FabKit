export module fbc.CardData;

import fbc.BaseContent;
import fbc.CardGroup;
import fbc.CardType;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.ObjectRarity;
import std;

namespace fbc {
	export class CardData : public GameObjectDataDerived<CardData> {
	public:
		struct CardTargeting {
			int targetRangeMax = 1;
			int targetRangeMaxUp = 0;
			int targetRangeMin = 1;
			int targetRangeMinUp = 0;
			int targetSizeX = 1;
			int targetSizeXUp = 0;
			int targetSizeY = 1;
			int targetSizeYUp = 0;
		};

		struct ExportFields {
			bool isUpgradeBranchOptional;
			bool targetAlly;
			bool targetEnemy;
			bool targetSquare;
			int costBase;
			int costUp;
			int maxCopies;
			int maxUpgrades;
			int targetRangeMax;
			int targetRangeMaxUp;
			int targetRangeMin;
			int targetRangeMinUp;
			int targetSizeX;
			int targetSizeXUp;
			int targetSizeY;
			int targetSizeYUp;
			str group;
			str type;
			str rarity;
			vec<str> effects;
			vec<str> tags;
			vec<str> upgradeBranches;
		};

		struct RuntimeFields {
			RuntimeFields() {}
			RuntimeFields(const ExportFields& fields) {
				isUpgradeBranchOptional = fields.isUpgradeBranchOptional;
				targetAlly = fields.targetAlly;
				targetEnemy = fields.targetEnemy;
				targetSquare = fields.targetSquare;
				costBase = fields.costBase;
				costUp = fields.costUp;
				maxCopies = fields.maxCopies;
				maxUpgrades = fields.maxUpgrades;
				target.targetRangeMax = fields.targetRangeMax;
				target.targetRangeMaxUp = fields.targetRangeMaxUp;
				target.targetRangeMin = fields.targetRangeMin;
				target.targetRangeMinUp = fields.targetRangeMinUp;
				target.targetSizeX = fields.targetSizeX;
				target.targetSizeXUp = fields.targetSizeXUp;
				target.targetSizeY = fields.targetSizeY;
				target.targetSizeYUp = fields.targetSizeYUp;
				group = CardGroup::get(fields.group);
				type = CardType::get(fields.type);
				rarity = ObjectRarity::get(fields.rarity);
				// TODO: Populate effects from fields.effects
				tags = fields.tags;
				upgradeBranches = fields.upgradeBranches;
			}
			RuntimeFields(RuntimeFields&& other) = default;

			bool isUpgradeBranchOptional = true;
			bool targetAlly = false;
			bool targetEnemy = true;
			bool targetSquare = false;
			CardGroup* group;
			CardTargeting target;
			CardType* type;
			int costBase = 1;
			int costUp = 0;
			int maxCopies = -1;
			int maxUpgrades = 1;
			ObjectRarity* rarity;
			vec<uptr<Effect>> effects;
			vec<str> tags;
			vec<str> upgradeBranches;
		};

		CardData(BaseContent& source, strv id) : GameObjectDataDerived(source, id) {}
		CardData(BaseContent& source, strv id, const ExportFields& fields) : GameObjectDataDerived(source, id) {}

		RuntimeFields data;

		inline int getCost(int level) const { return data.costBase + data.costUp * level; }

		ExportFields createExport() const;
	};


	CardData::ExportFields CardData::createExport() const
	{
		ExportFields fields = ExportFields();
		fields.isUpgradeBranchOptional = data.isUpgradeBranchOptional;
		fields.targetAlly = data.targetAlly;
		fields.targetEnemy = data.targetEnemy;
		fields.targetSquare = data.targetSquare;
		fields.costBase = data.costBase;
		fields.costUp = data.costUp;
		fields.maxCopies = data.maxCopies;
		fields.maxUpgrades = data.maxUpgrades;
		fields.targetRangeMax = data.target.targetRangeMax;
		fields.targetRangeMaxUp = data.target.targetRangeMaxUp;
		fields.targetRangeMin = data.target.targetRangeMin;
		fields.targetRangeMinUp = data.target.targetRangeMinUp;
		fields.targetSizeX = data.target.targetSizeX;
		fields.targetSizeXUp = data.target.targetSizeXUp;
		fields.targetSizeY = data.target.targetSizeY;
		fields.targetSizeYUp = data.target.targetSizeYUp;
		fields.group = data.group ? data.group->id : "";
		fields.type = data.type ? data.type->id : "";
		fields.rarity = data.rarity ? data.rarity->id : "";
		fields.tags = data.tags;
		fields.upgradeBranches = data.upgradeBranches;
		// TODO effects
		return fields;
	}
}