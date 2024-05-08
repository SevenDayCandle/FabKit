export module fbc.uiVerticalCanvas;

import fbc.coreConfig;
import fbc.hitbox;
import fbc.uiCanvas;
import fbc.futil;
import fbc.uiVerticalScrollbar;
import fbc.scaleHitbox;

export namespace fbc {
	export class UIVerticalCanvas : public UICanvas {
	public:
		UIVerticalCanvas(Hitbox* hb, float scrollSpeed = 1): UICanvas(hb),
			scrollSpeed(scrollSpeed),
			scrollbar{ new ScaleHitbox(hb->w * 0.93f / cfg.renderScale(), hb->y + hb->h * 0.05f / cfg.renderScale(), 48, hb->h * 0.9f / cfg.renderScale())},
			baseOffsetY(hb->getOffsetPosY()) {
			scrollbar.setOnScroll([this](float f) {reposition(f); });
		}
		virtual ~UIVerticalCanvas() {}

		inline void scroll(float percent) { scrollbar.scroll(percent); }
		inline void setScrollPos(float percent) { scrollbar.setScrollPos(percent); }

		UIVerticalCanvas& setScrollSpeed(float scrollSpeed);
		void renderImpl() override;
		void updateImpl() override;
	protected:
		float scrollSpeed;
		UIVerticalScrollbar scrollbar;
	private:
		float baseOffsetY;

		inline void reposition(float percent) { hb->setOffsetPosY(baseOffsetY - percent * scrollSpeed); }
	};

	UIVerticalCanvas& UIVerticalCanvas::setScrollSpeed(float scrollSpeed)
	{
		this->scrollSpeed = scrollSpeed;
		reposition(scrollbar.getScroll());
		return *this;
	}

	void UIVerticalCanvas::renderImpl()
	{
		UICanvas::renderImpl();
		scrollbar.renderImpl();
	}

	void UIVerticalCanvas::updateImpl()
	{
		UICanvas::updateImpl();
		scrollbar.updateImpl();
	}
}