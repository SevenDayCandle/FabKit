export module fbc.Action;

import fbc.FUtil;
import std;

namespace fbc {
	export struct Action {
	public:
		Action() {}
		virtual ~Action() = default;

		virtual inline bool run() { return true; }

		virtual void start() = 0;
	};
}