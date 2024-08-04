export module fbc.HitboxBatchMoveSmoothVFX;

import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class HitboxBatchMoveSmoothVFX : public CallbackVFX {
	public:
		struct Entry {
			Hitbox* hb;
			float tOffX;
			float tOffY;
		};

		HitboxBatchMoveSmoothVFX(vec<Entry>& items, float duration = DEFAULT_DURATION): HitboxBatchMoveSmoothVFX(items, duration, 9 / duration) {}
		HitboxBatchMoveSmoothVFX(vec<Entry>& items, float duration, float rate): CallbackVFX(duration), items(items), rate(rate) {}

		float rate;
		vec<Entry> items;

		inline virtual void render() override {}

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
		for (Entry& e : items) {
			float lx = std::lerp(e.hb->getOffPosX(), e.tOffX, rate * sdl::timeDelta());
			float ly = std::lerp(e.hb->getOffPosY(), e.tOffY, rate * sdl::timeDelta());
			e.hb->setOffPos(lx, ly);
		}
	}
}