export module fbc.SequentialAction;

import fbc.Action;
import fbc.CallbackAction;
import fbc.FUtil;
import std;

namespace fbc {
	export class SequentialAction : public CallbackAction<SequentialAction> {
	public:
		SequentialAction(): CallbackAction<SequentialAction>() {}
		virtual ~SequentialAction() = default;

		template <c_varg<uptr<Action>>... Args> SequentialAction& addActions(Args&&... items);
		virtual bool run() override;
		virtual void start() override;
	protected:
		vec<uptr<Action>> actions;
	private:
		int i = 0;
	};

	template<c_varg<uptr<Action>> ...Args> SequentialAction& SequentialAction::addActions(Args&&... items) {
		(actions.push_back(move(items)), ...);
		return *this;
	}

	inline bool SequentialAction::run() {
		if (i >= actions.size()) {
			return true;
		}
		if (actions[i]->run()) {
			if (!actions[i]->isSuccess()) {
				return true;
			}
			++i;
			if (i >= actions.size()) {
				return true;
			}
			actions[i]->start();
		}
		return false;
	}

	void SequentialAction::start() {
		if (i < actions.size()) {
			actions[i]->start();
		}
	}
}