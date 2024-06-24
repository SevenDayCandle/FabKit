export module fbc.PassiveData;

import fbc.BaseContent;
import fbc.Effect;
import fbc.FUtil;
import fbc.AttributeObjectData;
import sdl;
import std;

export namespace fbc {
	export class PassiveData : public AttributeObjectData {
	public:
		PassiveData(BaseContent& source, strv ID) : AttributeObjectData(source, ID) {}
		virtual ~PassiveData() {}

		int maxUpgrades = 0;
		vec<uptr<Effect>> effects;
	};
}