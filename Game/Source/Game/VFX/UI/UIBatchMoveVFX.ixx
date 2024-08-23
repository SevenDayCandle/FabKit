export module fbc.UIBatchMoveVFX;

import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.Hoverable;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIBatchMoveVFX : public CallbackVFX {
	public:
		struct Entry {
			Entry(Hoverable& hoverable, float tOffX, float tOffY): item(hoverable.makeToken()), tOffX(tOffX), tOffY(tOffY) {}

			Hoverable::Token item;
			float tOffX;
			float tOffY;
		};

		UIBatchMoveVFX(FWindow& window, float duration = DEFAULT_DURATION * 0.5f) : UIBatchMoveVFX(window, duration, defaultRate(duration)) {}
		UIBatchMoveVFX(FWindow& window, float duration, float rate) : CallbackVFX(window, duration), rate(rate) {}
		UIBatchMoveVFX(FWindow& window, vec<Entry>&& items, float duration = DEFAULT_DURATION * 0.5f): UIBatchMoveVFX(window, move(items), duration, defaultRate(duration)) {}
		UIBatchMoveVFX(FWindow& window, vec<Entry>&& items, float duration, float rate): CallbackVFX(window, duration), items(move(items)), rate(rate) {}

		float rate;
		vec<Entry> items;

		inline static float defaultRate(float duration) { return 15 / (sdl::NANOS_PER_SECOND * duration); }
		inline virtual void render(sdl::SDLBatchRenderPass& rp) override {}

		virtual void dispose() override;
		virtual void update() override;
	};

	void UIBatchMoveVFX::dispose()
	{
		for (Entry& e : items) {
			if (e.item) {
				e.item->setHbOffsetPos(e.tOffX, e.tOffY);
			}
		}
		CallbackVFX::dispose();
	}

	void UIBatchMoveVFX::update()
	{
		float lerp = rate * sdl::runner::timeDelta();
		for (Entry& e : items) {
			if (e.item) {
				Hitbox* hb = e.item->getHb();
				float lx = std::lerp(hb->getOffPosX(), e.tOffX, lerp);
				float ly = std::lerp(hb->getOffPosY(), e.tOffY, lerp);
				hb->setOffPos(lx, ly);
			}
		}
	}
}