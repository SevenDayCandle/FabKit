export module fbc.uiVerticalScrollbar;

import fbc.coreContent;
import fbc.futil;
import fbc.hitbox;
import fbc.uiScrollbar;

export namespace fbc {

	export class UIVerticalScrollbar : public UIScrollbar {
	public:
		UIVerticalScrollbar(Hitbox* hb): UIScrollbar(hb, cct.images.scrollbar(), cct.images.scrollbutton()) {
			updateDropzoneSize(0.05f);
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
		dropzone.y = hb->y + percent * actualRange;
	}

	void UIVerticalScrollbar::updateDropzoneSize(float percent)
	{
		dropzone.x = hb->x;
		dropzone.w = hb->w;
		dropzone.y = hb->y;
		dropzone.h = hb->h * percent;
		actualRange = hb->h - dropzone.h;
	}

}