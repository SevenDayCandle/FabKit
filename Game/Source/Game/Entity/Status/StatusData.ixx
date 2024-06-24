export module fbc.StatusData;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.AttributeObjectData;
import fbc.StatusTurnMode;
import std;

export namespace fbc {
	export class StatusData : public AttributeObjectData {
	public:
		StatusData(BaseContent& source, strv ID): AttributeObjectData(source, ID) {}
		virtual ~StatusData() {}

		bool removable;
		bool debuff;
		bool stacksIncreaseTurns;
		int maxStacks = futil::INT_MAX;
		int maxTurns = futil::INT_MAX;
		int minStacks = 0;
		int priority = 0;
		StatusTurnMode turnMode = StatusTurnMode::NONE;
		vec<uptr<Effect>> effects;
	};
}