export module fbc.UICallbackInteractable;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

namespace fbc {
	export template <typename T> class UICallbackInteractable : public UIInteractable {
	public:
		UICallbackInteractable(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIInteractable(window, move(hb), image) {}
		~UICallbackInteractable() override {}

		inline UICallbackInteractable& setOnClick(const func<void(T&)>& onClick) { return this->onLeftClick = onClick, *this; }
		inline UICallbackInteractable& setOnRightClick(const func<void(T&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }
	private:
		func<void(T&)> onLeftClick;
		func<void(T&)> onRightClick;

		inline virtual T& callbackObject() { return static_cast<T&>(*this); }

		virtual void clickLeftEvent() override;
		virtual void clickRightEvent() override;
	};

	template <typename T> void UICallbackInteractable<T>::clickLeftEvent() {
		if (this->onLeftClick) {
			this->onLeftClick(callbackObject());
		}
	}

	template <typename T> void UICallbackInteractable<T>::clickRightEvent() {
		if (this->onRightClick) {
			this->onRightClick(callbackObject());
		}
	}
}