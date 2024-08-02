export module fbc.VFX;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.IOverlay;
import sdl;
import std;

namespace fbc {
	export constexpr float DEFAULT_DURATION = 1;

	export class VFX : public IOverlay {
	public:
		VFX(float duration = DEFAULT_DURATION): duration(duration * cfg.gameEffectSpeed.get()) {}
		virtual ~VFX() override = default;

		float duration = DEFAULT_DURATION;
		float ticks = 0;

		virtual bool tickUpdate() override;
	};

	// Update the VFX and dispose when the duration is completed
	bool VFX::tickUpdate()
	{
		update();
		ticks += sdl::timeDelta();
		if (ticks >= duration) {
			dispose();
			return true;
		}
		return false;
	}
}