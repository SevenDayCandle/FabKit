export module fbc.UIHorizontalScrollbar;

import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIScrollbar;

export namespace fbc {
	export class UIHorizontalScrollbar : public UIScrollbar {
	public:
		UIHorizontalScrollbar(Hitbox* hb, IDrawable& imageBar = cct.images.scrollbar, IDrawable& imageButton = cct.images.scrollbutton) : UIScrollbar(hb, imageBar, imageButton) {
			UIHorizontalScrollbar::updateDropzoneSize(0.05f);
		}
		virtual ~UIHorizontalScrollbar() {}

		float toPercentage(float x, float y) override;
		void updateDropzonePos(float percent) override;
		void updateDropzoneSize(float percent) override;
	};


	float UIHorizontalScrollbar::toPercentage(float x, float y)
	{
		return (x - hb->x) / actualRange;
	}

	void UIHorizontalScrollbar::updateDropzonePos(float percent)
	{
		dropzone.x = hb->x + percent * actualRange;
		dropzone.y = hb->y;
	}

	void UIHorizontalScrollbar::updateDropzoneSize(float percent)
	{
		dropzone.w = hb->w * percent;
		dropzone.h = hb->h;
		actualRange = hb->w - dropzone.w;
	}
}