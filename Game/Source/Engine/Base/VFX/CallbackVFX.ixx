export module fbc.CallbackVFX;

import fbc.FUtil;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class CallbackVFX : public VFX {
	public:
		CallbackVFX(float duration = DEFAULT_DURATION): VFX(duration) {}
		virtual ~CallbackVFX() = default;

		func<void(CallbackVFX&)> onComplete;

		inline VFX& setOnComplete(const func<void(CallbackVFX&)>& onComplete) { return this->onComplete = onComplete, *this; }

		virtual void dispose() override;
	};

	 void CallbackVFX::dispose()
	{
		if (onComplete) {
			onComplete(*this);
		}
	}
}