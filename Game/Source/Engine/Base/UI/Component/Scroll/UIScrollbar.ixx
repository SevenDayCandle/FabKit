export module fbc.UIScrollbar;

import fbc.Hitbox;
import fbc.UIBase;
import fbc.FUtil;
import fbc.IDrawable;
import fbc.ScreenManager;
import sdl;
import std;

namespace fbc {
	export class UIScrollbar : public UIBase {
	public:
		UIScrollbar(Hitbox* hb, IDrawable& imageBar, IDrawable& imageButton): UIBase(hb), imageBar(imageBar), imageButton(imageButton) {
		}

		inline float getScroll() const { return scrollPercent; }
		inline UIScrollbar& setOnScroll(const func<void(float)>& onScroll) { return this->onScroll = onScroll, *this; }

		virtual void onSizeUpdated() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
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
		int scrollDiff = sdl::mouseGetWheelY();
		if (scrollDiff != 0) {
			scroll(getScroll() + scrollDiff * -0.05f);
		}
	}

	void UIScrollbar::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		imageBar.draw(hb.get());
		imageButton.draw(&dropzone);
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

		if (hb->isHovered() && sdl::mouseIsLeftJustClicked()) {
			screenManager::activeElement = this;
			float per = toPercentage(sdl::mouseGetX(), sdl::mouseGetY());
			clickPercent = per;
			if (!sdl::mouseIsHovering(dropzone)) {
				scroll(per);
			}
		}
		else if (screenManager::activeElement == this) {
			if (sdl::mouseIsLeftClicked()) {
				float per = toPercentage(sdl::mouseGetX(), sdl::mouseGetY());
				if (per != clickPercent) {
					scroll(scrollPercent + per - clickPercent);
					clickPercent = per;
				}
			}
			else {
				screenManager::activeElement = nullptr;
			}
		}
	}
}