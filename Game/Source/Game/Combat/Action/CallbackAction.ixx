export module fbc.CallbackAction;

import fbc.Action;
import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.ScreenManager;
import fbc.UIBase;
import std;

namespace fbc {
	export class CallbackAction : public Action {
	public:
		CallbackAction(const func<void()>& onStart): onStart(onStart) {}
		virtual ~CallbackAction() = default;

		func<void()> onStart;

		inline virtual void start() override { onStart(); }
	};
}