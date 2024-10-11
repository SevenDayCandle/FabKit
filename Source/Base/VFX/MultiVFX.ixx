export module fbc.MultiVFX;

import fbc.CallbackVFX; 
import fbc.FUtil;
import fbc.FWindow;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;
namespace fbc {
	export class MultiVFX : public CallbackVFX {
	public:
		MultiVFX(FWindow& window, float duration = DEFAULT_DURATION) : CallbackVFX(window, duration) {}
		virtual ~MultiVFX() = default;
	};
}