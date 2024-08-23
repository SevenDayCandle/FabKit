export module fbc.UIVerticalCanvas;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.ScaleHitbox;
import fbc.UICanvas;
import fbc.UIVerticalScrollbar;
import sdl.SDLBatchRenderPass;

namespace fbc {
	export class UIVerticalCanvas : public UICanvas {
	public:
		UIVerticalCanvas(FWindow& window, uptr<Hitbox>&& hb, float scrollSpeed = 1): UICanvas(window, move(hb)),
			scrollSpeed(scrollSpeed),
			scrollbar{ window, make_unique<ScaleHitbox>(window, hb->w * 0.93f / window.cfg.renderScale(), hb->y + hb->h * 0.05f / window.cfg.renderScale(), 48, hb->h * 0.9f / window.cfg.renderScale())},
			baseOffsetY(hb->getOffPosY()) {
			scrollbar.setOnScroll([this](float f) {reposition(f); });
		}

		inline void scroll(float percent) { scrollbar.scroll(percent); }
		inline void setScrollPos(float percent) { scrollbar.setScrollPos(percent); }

		UIVerticalCanvas& setScrollSpeed(float scrollSpeed);
		void refreshDimensions() override;
		void renderImpl(sdl::SDLBatchRenderPass& rp) override;
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

	void UIVerticalCanvas::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UICanvas::renderImpl(rp);
		scrollbar.renderImpl(rp);
	}

	void UIVerticalCanvas::updateImpl()
	{
		UICanvas::updateImpl();
		scrollbar.updateImpl();
	}
}