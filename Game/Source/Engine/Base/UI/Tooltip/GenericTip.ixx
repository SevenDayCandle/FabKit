export module fbc.GenericTip;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.FWindow;
import sdl;
import std;

namespace fbc {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float QUEUE_OFFSET_X = 36;
	export constexpr float QUEUE_OFFSET_Y = 18;

	export class GenericTip : public FWindow::Element {
	public:
		GenericTip(FWindow& window, float size = DEFAULT_SIZE): Element(window), bounds(0, 0, size, 0) {
			setupBounds();
		}
		virtual ~GenericTip() = default;

		inline GenericTip& setBoundsW(float w) { return bounds.w = w, *this; }
		inline virtual void update() override {}
		inline void queue() { queue(sdl::runner::mouseGetX() + cfg.renderScale(QUEUE_OFFSET_X), sdl::runner::mouseGetY() + cfg.renderScale(QUEUE_OFFSET_Y)); }

		virtual void queue(float x, float y);
	protected:
		sdl::RectF bounds;

		inline virtual void updateBounds() {}
	private:
		inline void setupBounds() { updateBounds(); }
	};

	// Queue this tooltip for rendering at a specific position
	void GenericTip::queue(float x, float y)
	{
		float xBound = win.getW();
		float yBound = win.getH();
		bounds.x = x + bounds.w >= xBound ? xBound - bounds.w : x;
		bounds.y = y + bounds.h >= xBound ? xBound - bounds.h : y;
		this->win.queueTip(this);
	}
}