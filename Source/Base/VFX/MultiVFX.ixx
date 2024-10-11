export module fab.MultiVFX;

import fab.CallbackVFX; 
import fab.FUtil;
import fab.FWindow;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;
namespace fab {
	export class MultiVFX : public CallbackVFX {
	public:
		MultiVFX(FWindow& window, float duration = DEFAULT_DURATION) : CallbackVFX(window, duration) {}
		virtual ~MultiVFX() = default;
	};
}