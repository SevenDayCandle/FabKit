export module fab.VFX;

import fab.FUtil;
import fab.FWindow;
import sdl.SDLBase;
import sdl.SDLRunner;
import std;

namespace fab {
	export constexpr float DEFAULT_DURATION = 1;

	export class VFX : public FWindow::Element {
	public:
		VFX(FWindow& window, float duration = DEFAULT_DURATION): Element(window), duration(duration * sdl::NANOS_PER_SECOND * window.effectSpeed()) {}
		virtual ~VFX() override = default;

		float duration;
		float ticks = 0;

		virtual bool tickUpdate();

		inline static float cubic(float ticks, float duration) { return 1 - std::pow(1 - ticks / duration, 3); };
		inline static float linear(float ticks, float duration) { return ticks / duration; };
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