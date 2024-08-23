export module fbc.UIHorizontalScrollbar;

import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIScrollbar;

namespace fbc {
	export class UIHorizontalScrollbar : public UIScrollbar {
	public:
		UIHorizontalScrollbar(FWindow& window, uptr<Hitbox>&& hb, IDrawable& imageBar, IDrawable& imageButton) :
			UIScrollbar(window, move(hb), imageBar, imageButton) {
			UIHorizontalScrollbar::updateDropzoneSize(0.05f);
		}
		UIHorizontalScrollbar(FWindow& window, uptr<Hitbox>&& hb) :
			UIHorizontalScrollbar(window, move(hb), window.cct.images.uiScrollbar, window.cct.images.uiScrollbutton) {}

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