export module fab.UIScrollbar;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;

import fab.UIBase;
import sdl.SDLBase; 
import fab.BatchRenderPass; 
import sdl.SDLRunner;
import std;

namespace fab {
	export class UIScrollbar : public UIBase {
	public:
		UIScrollbar(FWindow& window, uptr<Hitbox>&& hb, IDrawable& imageBar, IDrawable& imageButton): UIBase(window, move(hb)), imageBar(imageBar), imageButton(imageButton) {}

		inline float getScroll() const { return scrollPercent; }
		inline UIScrollbar& setOnScroll(const func<void(float)>& onScroll) { return this->onScroll = onScroll, *this; }
		inline UIScrollbar& setOnScroll(func<void(float)>&& onScroll) { return this->onScroll = move(onScroll), *this; }

		virtual void onSizeUpdated() override;
		virtual void renderImpl(BatchRenderPass& rp) override;
		virtual void updateImpl() override;
		void processMouseScroll();
		void scroll(float percent);
		void setScrollPos(float percent);
		virtual float toPercentage(float x, float y) = 0;
		virtual void updateDropzonePos(float percent) = 0;
		virtual void updateDropzoneSize(float percent) = 0;
	protected:
		float actualRange;
		IDrawable& imageBar;
		IDrawable& imageButton;
		sdl::RectF dropzone;
	private:
		float clickPercent = -1;
		float scrollPercent;
		func<void(float)> onScroll;
	};

	void UIScrollbar::onSizeUpdated()
	{
		UIBase::onSizeUpdated();
		updateDropzonePos(scrollPercent);
		updateDropzoneSize(0.05f);
	}

	void UIScrollbar::processMouseScroll()
	{
		int scrollDiff = sdl::runner::mouseGetWheelY();
		if (scrollDiff != 0) {
			scroll(getScroll() + scrollDiff * -0.05f);
		}
	}

	void UIScrollbar::renderImpl(BatchRenderPass& rp) {
		imageBar.draw(rp, *hb.get());
		imageButton.draw(rp, dropzone);
	}

	// Updates the scrollbar button position and triggers the scroll event at the new position
	void UIScrollbar::scroll(float percent)
	{
		setScrollPos(percent);
		onScroll(scrollPercent);
	}

	// Updates the position of the scrollbar button without actually triggering the scroll event
	void UIScrollbar::setScrollPos(float percent)
	{
		scrollPercent = std::clamp(percent, 0.0f, 1.0f);
	}

	void UIScrollbar::updateImpl() {
		UIBase::updateImpl();
		updateDropzonePos(scrollPercent);

		if (hb->isHovered() && sdl::runner::mouseIsLeftJustClicked()) {
			this->win.activeElement = this;
			float per = toPercentage(sdl::runner::mouseGetX(), sdl::runner::mouseGetY());
			clickPercent = per;
			if (!sdl::runner::mouseIsHovering(dropzone)) {
				scroll(per);
			}
		}
		else if (this->win.activeElement == this) {
			if (sdl::runner::mouseIsLeftClicked()) {
				float per = toPercentage(sdl::runner::mouseGetX(), sdl::runner::mouseGetY());
				if (per != clickPercent) {
					scroll(scrollPercent + per - clickPercent);
					clickPercent = per;
				}
			}
			else {
				this->win.activeElement = nullptr;
			}
		}
	}
}