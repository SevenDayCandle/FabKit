export module fbc.UIHorizontalScrollbar;

import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIScrollbar;

export namespace fbc {
	export class UIHorizontalScrollbar : public UIScrollbar {
	public:
		UIHorizontalScrollbar(Hitbox* hb) : UIScrollbar(hb, cct.images.scrollbar(), cct.images.scrollbutton()) {
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
	}

	void UIHorizontalScrollbar::updateDropzoneSize(float percent)
	{
		dropzone.x = hb->x;
		dropzone.w = hb->w * percent;
		dropzone.y = hb->y;
		dropzone.h = hb->h;
		actualRange = hb->w - dropzone.w;
	}
}