export module fab.UIVerticalCanvas;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.Hoverable;
import fab.ScaleHitbox;
import fab.UICanvas;
import fab.UIVerticalScrollbar;
import fab.BatchRenderPass;

namespace fab {
	export template<c_ext<Hoverable> T = Hoverable> class UIVerticalCanvas : public UICanvas<T> {
	public:
		UIVerticalCanvas(FWindow& window, uptr<Hitbox>&& hb, float scrollSpeed = 1): UICanvas<T>(window, move(hb)),
			scrollSpeed(scrollSpeed),
			scrollbar{ window, make_unique<ScaleHitbox>(window, hb->w * 0.93f / window.renderScale(), hb->y + hb->h * 0.05f / window.renderScale(), 48, hb->h * 0.9f / window.renderScale())},
			baseOffsetY(hb->getOffPosY()) {
			scrollbar.setOnScroll([this](float f) {reposition(f); });
		}

		inline void scroll(float percent) { scrollbar.scroll(percent); }
		inline void setScrollPos(float percent) { scrollbar.setScrollPos(percent); }

		UIVerticalCanvas& setScrollSpeed(float scrollSpeed);
		void refreshDimensions() override;
		void renderImpl(BatchRenderPass& rp) override;
		void updateImpl() override;
	protected:
		float scrollSpeed;
		UIVerticalScrollbar scrollbar;
	private:
		float baseOffsetY;

		inline void reposition(float percent) { this->hb->setOffPosY(baseOffsetY - percent * scrollSpeed); }
	};

	template<c_ext<Hoverable> T> UIVerticalCanvas<T>& UIVerticalCanvas<T>::setScrollSpeed(float scrollSpeed)
	{
		this->scrollSpeed = scrollSpeed;
		reposition(scrollbar.getScroll());
		return *this;
	}

	template<c_ext<Hoverable> T> void UIVerticalCanvas<T>::refreshDimensions()
	{
		UICanvas<T>::refreshDimensions();
		scrollbar.refreshDimensions();
	}

	template<c_ext<Hoverable> T> void UIVerticalCanvas<T>::renderImpl(BatchRenderPass& rp)
	{
		UICanvas<T>::renderImpl(rp);
		scrollbar.renderImpl(rp);
	}

	template<c_ext<Hoverable> T> void UIVerticalCanvas<T>::updateImpl()
	{
		UICanvas<T>::updateImpl();
		scrollbar.updateImpl();
	}
}