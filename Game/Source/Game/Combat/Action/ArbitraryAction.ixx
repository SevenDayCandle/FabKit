export module fbc.ArbitraryAction;

import fbc.Action;
import fbc.FUtil;
import std;

namespace fbc {
	export class ArbitraryAction : public Action {
	public:
		ArbitraryAction(const func<void()>& onStart): onStart(onStart) {}
		virtual ~ArbitraryAction() = default;

		func<void()> onStart;

		inline virtual void start() override { onStart(); }
	};
}