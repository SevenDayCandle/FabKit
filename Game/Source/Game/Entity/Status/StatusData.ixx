export module fbc.StatusData;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObjectData;
import fbc.StatusTurnMode;
import std;

namespace fbc {
	export class StatusData : public GameObjectData<StatusData> {
	public:
		static constexpr cstr FOLDER = "Statuses";
		static constexpr cstr LOCPATH = "StatusStrings";

		struct Fields {
			bool removable;
			bool debuff;
			bool stacksIncreaseTurns;
			int maxStacks = futil::INT_MAX;
			int maxTurns = futil::INT_MAX;
			int minStacks = 0;
			int priority = 0;
			StatusTurnMode turnMode = StatusTurnMode::NONE;
		};

		StatusData(BaseContent& source, strv id): GameObjectData(source, id) {}
		StatusData(BaseContent& source, strv id, const Fields& fields) : GameObjectData(source, id), data(fields) {}

		Fields data;
		vec<uptr<Effect>> effects;
	};
}