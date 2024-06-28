export module fbc.Passive;

import fbc.AttributeObject;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PassiveData;
import sdl;
import std;

namespace fbc {
	export class Passive : public GameObjectDerived<PassiveData>, public AttributeObject {
	public:
		Passive(PassiveData& data) : GameObjectDerived<PassiveData>(data) {}
		virtual ~Passive() {}

		int upgrades;
	};
}