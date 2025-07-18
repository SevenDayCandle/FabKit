export module fab.UIVerticalScrollbar;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.UIScrollbar;
import sdl.SDLBase; 
import fab.BatchRenderPass; 
import sdl.SDLRunner;

namespace fab {

	export class UIVerticalScrollbar : public UIScrollbar {
	public:
		UIVerticalScrollbar(FWindow& window, uptr<Hitbox>&& hb, IDrawable& imageBar, IDrawable& imageButton) :
			UIScrollbar(window, move(hb), imageBar, imageButton) {
			UIVerticalScrollbar::updateDropzoneSize(0.05f);
		}
		UIVerticalScrollbar(FWindow& window, uptr<Hitbox>&& hb) :
			UIVerticalScrollbar(window, move(hb), window.props.defaultScrollBack(), window.props.defaultScrollButton()) {}


		float toPercentage(float x, float y) override;
		void updateDropzonePos(float percent) override;
		void updateDropzoneSize(float percent) override;
	};


	float UIVerticalScrollbar::toPercentage(float x, float y)
	{
		return (y - hb->y) / actualRange;
	}

	void UIVerticalScrollbar::updateDropzonePos(float percent)
	{
		dropzone.x = hb->x;
		dropzone.y = hb->y + percent * actualRange;
	}

	void UIVerticalScrollbar::updateDropzoneSize(float percent)
	{
		dropzone.w = hb->w;
		dropzone.h = hb->h * percent;
		actualRange = hb->h - dropzone.h;
	}

}