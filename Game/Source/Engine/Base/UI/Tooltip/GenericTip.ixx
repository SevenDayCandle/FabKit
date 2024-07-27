export module fbc.GenericTip;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.IOverlay;
import fbc.ScreenManager;
import sdl;
import std;

namespace fbc {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float QUEUE_OFFSET_X = 36;
	export constexpr float QUEUE_OFFSET_Y = 18;

	export class GenericTip : public IOverlay {
	public:
		GenericTip(float size = DEFAULT_SIZE): bounds(0, 0, size, 0) {
			setupBounds();
		}
		virtual ~GenericTip() = default;

		inline GenericTip& setBoundsW(float w) { return bounds.w = w, *this; }
		inline virtual void update() override {}

		virtual void queue(float x = sdl::mouseGetX() + cfg.renderScale(QUEUE_OFFSET_X), float y = sdl::mouseGetY() + cfg.renderScale(QUEUE_OFFSET_Y));
	protected:
		sdl::RectF bounds;

		inline virtual void updateBounds() {}
	private:
		inline void setupBounds() { updateBounds(); }
	};

	// Queue this tooltip for rendering at a specific position
	void GenericTip::queue(float x, float y)
	{
		float xBound = cfg.getScreenXSize();
		float yBound = cfg.getScreenYSize();
		bounds.x = x + bounds.w >= xBound ? xBound - bounds.w : x;
		bounds.y = y + bounds.h >= xBound ? xBound - bounds.h : y;
		screenManager::queueTip(this);
	}
}