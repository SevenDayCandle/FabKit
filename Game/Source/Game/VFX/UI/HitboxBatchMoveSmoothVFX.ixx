export module fbc.HitboxBatchMoveSmoothVFX;

import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class HitboxBatchMoveSmoothVFX : public CallbackVFX {
	public:
		struct Entry {
			Hitbox* hb;
			float tOffX;
			float tOffY;
		};

		HitboxBatchMoveSmoothVFX(FWindow& window, vec<Entry>& items, float duration = DEFAULT_DURATION): HitboxBatchMoveSmoothVFX(window, items, duration, 15 / (sdl::NANOS_PER_SECOND * duration)) {}
		HitboxBatchMoveSmoothVFX(FWindow& window, vec<Entry>& items, float duration, float rate): CallbackVFX(window, duration), items(items), rate(rate) {}

		float rate;
		vec<Entry> items;

		inline virtual void render(sdl::SDLBatchRenderPass& rp) override {}

		virtual void dispose() override;
		virtual void update() override;
	};

	void HitboxBatchMoveSmoothVFX::dispose()
	{
		for (Entry& e : items) {
			e.hb->setOffPos(e.tOffX, e.tOffY);
		}
		CallbackVFX::dispose();
	}

	void HitboxBatchMoveSmoothVFX::update()
	{
		float lerp = rate * sdl::runner::timeDelta();
		for (Entry& e : items) {
			float lx = std::lerp(e.hb->getOffPosX(), e.tOffX, lerp);
			float ly = std::lerp(e.hb->getOffPosY(), e.tOffY, lerp);
			e.hb->setOffPos(lx, ly);
		}
	}
}