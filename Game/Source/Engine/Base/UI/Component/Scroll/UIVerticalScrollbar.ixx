export module fbc.UIVerticalScrollbar;

import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIScrollbar;
import sdl;

namespace fbc {

	export class UIVerticalScrollbar : public UIScrollbar {
	public:
		UIVerticalScrollbar(Hitbox* hb, IDrawable& imageBar = cct.images.scrollbar, IDrawable& imageButton = cct.images.scrollbutton): UIScrollbar(hb, imageBar, imageButton) {
			UIVerticalScrollbar::updateDropzoneSize(0.05f);
		}
		virtual ~UIVerticalScrollbar() {}

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