export module fab.GenericTip;

import fab.FUtil;
import fab.FWindow;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export constexpr float QUEUE_OFFSET_X = 36;
	export constexpr float QUEUE_OFFSET_Y = 18;

	export class GenericTip : public FWindow::Element {
	public:
		GenericTip(FWindow& window) : Element(window) {}
		virtual ~GenericTip() = default;

		inline virtual void update() override {}
		inline void queue() { queue(sdl::runner::mouseGetX() + win.renderScale(QUEUE_OFFSET_X), sdl::runner::mouseGetY() + win.renderScale(QUEUE_OFFSET_Y)); }

		virtual void queue(float x, float y);

		virtual float getHeight() const = 0;
		virtual float getWidth() const = 0;
	protected:
		float x;
		float y;

		inline virtual void updateBounds() {}
	};

	// Queue this tooltip for rendering at a specific position
	void GenericTip::queue(float x, float y)
	{
		float xBound = win.getW();
		float yBound = win.getH();
		float w = getWidth();
		float h = getHeight();
		x = x + w >= xBound ? xBound - w : x;
		y = y + h >= xBound ? xBound - h : y;
		this->win.queueTip(this);
	}
}