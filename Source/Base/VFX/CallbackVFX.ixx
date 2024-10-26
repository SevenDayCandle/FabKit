export module fab.CallbackVFX;

import fab.FUtil;
import fab.FWindow;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class CallbackVFX : public VFX {
	public:
		CallbackVFX(FWindow& window, float duration = DEFAULT_DURATION): VFX(window, duration) {}
		virtual ~CallbackVFX() = default;

		CallbackVFX& addOnComplete(const func<void(CallbackVFX&)>& onComplete);

		inline void render(sdl::SDLBatchRenderPass& rp) override {}
		inline void update() override {}

		virtual void dispose() override;

		inline static float defaultRate(float duration) { return 15 / (sdl::NANOS_PER_SECOND * duration); }
	protected:
		func<void(CallbackVFX&)> onComplete;
	};

	CallbackVFX& CallbackVFX::addOnComplete(const func<void(CallbackVFX&)>& onComplete) {
		auto prev = this->onComplete;
		if (prev) {
			this->onComplete = [prev, onComplete](CallbackVFX& val) {
				prev(val);
				onComplete(val);
			};
		}
		else {
			this->onComplete = onComplete;
		}
		return *this;
	}

	void CallbackVFX::dispose()
	{
		if (onComplete) {
			onComplete(*this);
		}
	}
}