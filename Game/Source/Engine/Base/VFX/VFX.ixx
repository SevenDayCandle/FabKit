export module fbc.VFX;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import sdl;
import std;

namespace fbc {
	export constexpr float DEFAULT_DURATION = 1;

	export class VFX : public IOverlay {
	public:
		VFX(float duration = DEFAULT_DURATION): duration(duration) {}
		virtual ~VFX() override = default;

		float duration = DEFAULT_DURATION;
		float ticks = 0;
		opt<func<void(VFX&)>> onComplete;

		inline VFX& setOnComplete(func<void(VFX&)>& onComplete) { return this->onComplete = onComplete, *this; }

		virtual void dispose() override;
		virtual bool tickUpdate() override;
	};

	void VFX::dispose()
	{
		if (onComplete) {
			(*onComplete)(*this);
		}
	}

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