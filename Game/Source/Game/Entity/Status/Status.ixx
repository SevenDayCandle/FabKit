export module fbc.Status;

import fbc.AttributeObject;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import fbc.StatusData;
import sdl;
import std;

namespace fbc {
	export class Status : public GameObjectDerived<StatusData>, public AttributeObject {
	public:
		Status(StatusData& data): GameObjectDerived<StatusData>(data) {}

		int stacks;
		int turns;
	};
}