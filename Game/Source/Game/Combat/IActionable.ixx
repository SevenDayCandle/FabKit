export module fbc.IActionable;

import fbc.FUtil;
import std;

namespace fbc {
	export struct IActionable {
	public:
		IActionable() {}
		virtual ~IActionable() = default;

		inline virtual bool isDone() { return true; }

		virtual void start() = 0;
	};
}