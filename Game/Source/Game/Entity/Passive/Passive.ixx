export module fbc.Passive;

import fbc.AttributeObject;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import fbc.PassiveData;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class Passive : public GameObjectD<PassiveData>, public AttributeObject {
	public:
		Passive(PassiveData& data, int upgrades = 0) : GameObjectD<PassiveData>(data), upgrades(upgrades) {}

		int upgrades;

		virtual void act() {}
	};
}