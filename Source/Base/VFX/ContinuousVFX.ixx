export module fbc.ContinuousVFX;

import fbc.CallbackVFX; 
import fbc.FUtil;
import fbc.FWindow;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class ContinuousVFX : public CallbackVFX {
	public:
		ContinuousVFX(FWindow& window, const func<bool()>& endCondition, float duration = DEFAULT_DURATION) : CallbackVFX(window, duration), endCondition(endCondition) {}
		virtual ~ContinuousVFX() = default;

		func<bool()> endCondition;

		virtual bool tickUpdate() override;
	};

	// Upon reaching duration, loop back to the beginning, then terminate if endCondition is satisfied
	bool ContinuousVFX::tickUpdate() {
		update();
		ticks += sdl::runner::timeDelta();
		if (ticks >= duration) {
			ticks = 0;
			if (endCondition()) {
				dispose();
				return true;
			}
		}
		return false;
	}
}