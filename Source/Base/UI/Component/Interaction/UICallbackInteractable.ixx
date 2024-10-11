export module fab.UICallbackInteractable;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

namespace fab {
	export template <typename T> class UICallbackInteractable : public UIInteractable {
	public:
		UICallbackInteractable(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIInteractable(window, move(hb), image) {}
		~UICallbackInteractable() override {}

		inline UICallbackInteractable& setOnClick(const func<void(T&)>& onClick) { return this->onLeftClick = onClick, *this; }
		inline UICallbackInteractable& setOnClick(func<void(T&)>&& onClick) { return this->onLeftClick = move(onClick), *this; }
		inline UICallbackInteractable& setOnRightClick(const func<void(T&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }
		inline UICallbackInteractable& setOnRightClick(func<void(T&)>&& onRightClick) { return this->onRightClick = move(onRightClick), *this; }
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