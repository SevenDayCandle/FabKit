export module fbc.Status;

import fbc.Effect;
import fbc.FUtil;
import fbc.AttributeObject;
import fbc.StatusData;
import sdl;
import std;

export namespace fbc {
	export class Status : public AttributeObject<StatusData> {
	public:
		Status(StatusData& data): AttributeObject<StatusData>(data) {}
		virtual ~Status() {}

		int stacks;
		int turns;
	};
}