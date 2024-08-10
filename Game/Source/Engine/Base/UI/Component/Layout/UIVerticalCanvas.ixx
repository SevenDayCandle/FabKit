export module fbc.UIVerticalCanvas;

import fbc.CoreConfig;
import fbc.Hitbox;
import fbc.UICanvas;
import fbc.FUtil;
import fbc.UIVerticalScrollbar;
import fbc.ScaleHitbox;

namespace fbc {
	export class UIVerticalCanvas : public UICanvas {
	public:
		UIVerticalCanvas(Hitbox* hb, float scrollSpeed = 1): UICanvas(hb),
			scrollSpeed(scrollSpeed),
			scrollbar{ new ScaleHitbox(hb->w * 0.93f / cfg.renderScale(), hb->y + hb->h * 0.05f / cfg.renderScale(), 48, hb->h * 0.9f / cfg.renderScale())},
			baseOffsetY(hb->getOffPosY()) {
			scrollbar.setOnScroll([this](float f) {reposition(f); });
		}

		inline void scroll(float percent) { scrollbar.scroll(percent); }
		inline void setScrollPos(float percent) { scrollbar.setScrollPos(percent); }

		UIVerticalCanvas& setScrollSpeed(float scrollSpeed);
		void refreshDimensions() override;
		void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		void updateImpl() override;
	protected:
		float scrollSpeed;
		UIVerticalScrollbar scrollbar;
	private:
		float baseOffsetY;

		inline void reposition(float percent) { hb->setOffPosY(baseOffsetY - percent * scrollSpeed); }
	};

	UIVerticalCanvas& UIVerticalCanvas::setScrollSpeed(float scrollSpeed)
	{
		this->scrollSpeed = scrollSpeed;
		reposition(scrollbar.getScroll());
		return *this;
	}

	void UIVerticalCanvas::refreshDimensions()
	{
		UICanvas::refreshDimensions();
		scrollbar.refreshDimensions();
	}

	void UIVerticalCanvas::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		UICanvas::renderImpl(cd, rp);
		scrollbar.renderImpl(cd, rp);
	}

	void UIVerticalCanvas::updateImpl()
	{
		UICanvas::updateImpl();
		scrollbar.updateImpl();
	}
}