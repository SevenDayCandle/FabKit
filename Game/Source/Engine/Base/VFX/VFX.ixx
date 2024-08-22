export module fbc.VFX;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.FWindow;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr float DEFAULT_DURATION = 1;

	export class VFX : public FWindow::Element {
	public:
		VFX(FWindow& window, float duration = DEFAULT_DURATION): Element(window), duration(duration * sdl::NANOS_PER_SECOND * cfg.gameEffectSpeed.get()) {}
		virtual ~VFX() override = default;

		float duration;
		float ticks = 0;

		virtual bool tickUpdate() override;
	};

	// Update the VFX and dispose when the duration is completed
	bool VFX::tickUpdate()
	{
		update();
		ticks += sdl::runner::timeDelta();
		if (ticks >= duration) {
			dispose();
			return true;
		}
		return false;
	}
}