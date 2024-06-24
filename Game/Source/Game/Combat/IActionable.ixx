export module fbc.IActionable;

import fbc.FUtil;
import std;

export namespace fbc {
	export struct IActionable {
	public:
		IActionable() {}
		virtual ~IActionable() {}

		inline virtual bool isDone() { return true; }

		virtual void start() = 0;
	};
}