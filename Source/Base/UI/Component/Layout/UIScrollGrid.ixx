export module fab.UIScrollGrid;

import fab.FWindow;
import fab.Hitbox;
import fab.UIBase;
import fab.UIGrid;
import fab.UIVerticalScrollbar;
import fab.FUtil;
import fab.ScaleHitbox;
import sdl.SDLBatchRenderPass;
import std;

namespace fab {
	export template <c_ext<UIBase> T> class UIScrollGrid : public UIGrid<T> {
	public:
		UIScrollGrid(FWindow& window, uptr<Hitbox>&& hb, float spacingX = 0, float spacingY = 0, float scrollSpeed = 1): UIGrid<T>(window, move(hb), spacingX, spacingY), scrollSpeed(scrollSpeed),
			scrollbar{ window, make_unique<ScaleHitbox>(window, this->hb->w * 0.93f / window.renderScale(), this->hb->y + this->hb->h * 0.05f / window.renderScale(), 48, this->hb->h * 0.9f / window.renderScale()) } {
			scrollbar.enabled = false;
		}
		UIScrollGrid(UIScrollGrid&& other) noexcept : UIGrid<T>(move(other.hb)), scrollSpeed(other.scrollSpeed), scrollbar(move(other.scrollbar)) {}
		virtual ~UIScrollGrid() = default;

		virtual bool isHovered() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		float scrollSpeed = 1;
		UIVerticalScrollbar scrollbar;

		virtual float updateItemOffsets(int begin, int end) override;
	};

	template<c_ext<UIBase> T> bool UIScrollGrid<T>::isHovered() {
		return UIGrid<T>::isHovered() || scrollbar.isHovered();
	}

	template<c_ext<UIBase> T> void UIScrollGrid<T>::refreshDimensions() {
		UIGrid<T>::refreshDimensions();
		scrollbar.refreshDimensions();
	}

	template<c_ext<UIBase> T> void UIScrollGrid<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIGrid<T>::renderImpl(rp);
		scrollbar.render(rp);
	}

	template<c_ext<UIBase> T> void UIScrollGrid<T>::updateImpl() {
		UIGrid<T>::updateImpl();
		scrollbar.update();
	}

	template<c_ext<UIBase> T> float UIScrollGrid<T>::updateItemOffsets(int begin, int end) {
		float y = UIGrid<T>::updateItemOffsets(begin, end);
		scrollbar.enabled = y > this->hb->y + this->hb->h;
		return y;
	}
}