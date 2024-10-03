export module fbc.SequentialAction;

import fbc.Action;
import fbc.CallbackAction;
import fbc.FUtil;
import std;

namespace fbc {
	export class SequentialAction : public CallbackAction<SequentialAction> {
	public:
		SequentialAction(): CallbackAction<SequentialAction>() {}
		template <c_varg<uptr<Action>>... Args> SequentialAction(Args&&... items) : CallbackAction<SequentialAction>() {
			actions.reserve(sizeof...(items));
			(actions.push_back(move(items)), ...);
		}
		virtual ~SequentialAction() = default;

		inline bool isSuccess() override { return executeIndex >= actions.size(); }
		inline int executedCount() const { return executeIndex; }
		inline int totalCount() const { return actions.size(); }
		inline SequentialAction& addAction(uptr<Action>&& act) { return actions.push_back(move(act)), * this; }
		template <c_varg<uptr<Action>&&>... Args> inline SequentialAction& addActions(Args&&... items) { return (actions.push_back(move(items)), ...), * this; }

		virtual bool run() override;
		virtual void start() override;
	protected:
		vec<uptr<Action>> actions;
	private:
		int executeIndex = 0;
	};

	inline bool SequentialAction::run() {
		if (executeIndex >= actions.size()) {
			return true;
		}
		if (actions[executeIndex]->run()) {
			if (!actions[executeIndex]->isSuccess()) {
				return true;
			}
			++executeIndex;
			if (executeIndex >= actions.size()) {
				return true;
			}
			actions[executeIndex]->start();
		}
		return false;
	}

	void SequentialAction::start() {
		if (executeIndex < actions.size()) {
			actions[executeIndex]->start();
		}
	}
}