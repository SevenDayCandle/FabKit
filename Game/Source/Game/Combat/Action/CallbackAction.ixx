export module fbc.CallbackAction;

import fbc.Action;
import fbc.FUtil;
import std;

namespace fbc {
	export template <typename T> class CallbackAction : public Action {
	public:
		CallbackAction(): Action() {}
		CallbackAction(const func<void(T&)>& onComplete) : Action(), onComplete(onComplete) {}
		virtual ~CallbackAction() = default;

		inline CallbackAction& setOnComplete(const func<void(T&)>& onComplete) { return this->onComplete = onComplete, *this; }

		virtual inline void complete() override;
	protected:
		func<void(T&)> onComplete;
	};

	template<typename T> inline void CallbackAction<T>::complete() {
		if (onComplete) {
			onComplete(static_cast<T&>(*this));
		}
	}
}