export module fbc.UIButton;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

namespace fbc {
	export class UIButton : public UIInteractable {
	public:
		UIButton(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIInteractable(window, move(hb), image) {}
		~UIButton() override {}

		inline UIButton& setOnClick(const func<void(UIButton&)>& onClick) { return this->onLeftClick = onClick, *this; }
		inline UIButton& setOnClick(func<void(UIButton&)>&& onClick) { return this->onLeftClick = move(onClick), *this; }
		inline UIButton& setOnRightClick(const func<void(UIButton&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }
		inline UIButton& setOnRightClick(func<void(UIButton&)>&& onRightClick) { return this->onRightClick = move(onRightClick), *this; }

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	private:
		func<void(UIButton&)> onLeftClick;
		func<void(UIButton&)> onRightClick;

		virtual void clickLeftEvent() override;
		virtual void clickRightEvent() override;
	};

	void UIButton::renderImpl(sdl::SDLBatchRenderPass& rp) {
		image.draw(rp, *hb.get(), win.getW(), win.getH(), scaleX, scaleY, rotation, hb->isHovered() && interactable ? &sdl::COLOR_WHITE : &color);
	}

	void UIButton::clickLeftEvent()
	{
		if (this->onLeftClick) {
			this->onLeftClick(*this);
		}
	}

	void UIButton::clickRightEvent()
	{
		if (this->onRightClick) {
			this->onRightClick(*this);
		}
	}
}
