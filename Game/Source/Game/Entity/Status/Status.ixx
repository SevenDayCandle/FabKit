export module fbc.Status;

import fbc.AttributeObject;
import fbc.Effect;
import fbc.FUtil;
import fbc.GameObject;
import fbc.StatusData;
import sdl;
import std;

namespace fbc {
	export class Status : public GameObjectD<StatusData>, public AttributeObject {
	public:
		Status(StatusData& data): GameObjectD<StatusData>(data) {}

		int stacks;
		int turns;
	};
}