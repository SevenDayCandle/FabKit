export module fbc.CallbackVFX;

import fbc.FUtil;
import fbc.FWindow;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class CallbackVFX : public VFX {
	public:
		CallbackVFX(FWindow& window, float duration = DEFAULT_DURATION): VFX(window, duration) {}
		virtual ~CallbackVFX() = default;

		func<void(CallbackVFX&)> onComplete;

		inline VFX& setOnComplete(const func<void(CallbackVFX&)>& onComplete) { return this->onComplete = onComplete, *this; }

		virtual void dispose() override;

		inline static float defaultRate(float duration) { return 15 / (sdl::NANOS_PER_SECOND * duration); }
	};

	 void CallbackVFX::dispose()
	{
		if (onComplete) {
			onComplete(*this);
		}
	}
}