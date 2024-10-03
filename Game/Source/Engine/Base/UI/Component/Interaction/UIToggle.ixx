export module fbc.UIToggle;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextDrawable;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIToggle : public UIInteractable {
	public:
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f, float xOff, float yOff) :
			UIInteractable(window, move(hb), image), checkImage(checkImage), text(f, text), offX(xOff), offY(yOff) {
			UIToggle::onSizeUpdated();
		}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f, float xOff) :
			UIToggle(window, move(hb), text, image, checkImage, f, xOff, image.getHeight() * 0.25f) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f) :
			UIToggle(window, move(hb), text, image, checkImage, f,
				image.getWidth() * 1.15f, image.getHeight() * 0.25f) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage) :
			UIToggle(window, move(hb), text, image, checkImage, window.cct.fontRegular()) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text) :
			UIToggle(window, move(hb), text, window.cct.images.uiCheckboxEmpty, window.cct.images.uiCheckboxFilled, window.cct.fontRegular()) {}

		bool toggled = false;
		IDrawable& checkImage;

		inline float getBeginX() override { return std::min(hb->x, hb->x + posX); }
		inline float getBeginY() override { return std::min(hb->y, hb->y + posY); }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setOnClick(func<void(UIToggle&)>&& onClick) { return this->onClick = move(onClick), *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		UIToggle& setTextOffset(float xOff, float yOff);
		void onSizeUpdated() override;
		void refreshDimensions() override;
		void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		void toggle(bool val);
	protected:
		TextDrawable text;
	private:
		func<void(UIToggle&)> onClick;
		float offX = 0;
		float offY = 0;
		float posX = 0;
		float posY = 0;

		virtual void clickLeftEvent() override;
	};

	UIToggle& UIToggle::setTextOffset(float xOff, float yOff) {
		this->offX = xOff;
		this->offY = yOff;
		onSizeUpdated();
		return *this;
	}

	void UIToggle::onSizeUpdated() {
		this->posX = win.cfg.renderScale(offX);
		this->posY = win.cfg.renderScale(offY);
	}

	void UIToggle::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		text.reload();
	}

	void UIToggle::renderImpl(sdl::SDLBatchRenderPass& rp) {
		if (toggled) {
			checkImage.draw(rp, *hb.get(), win.getW(), win.getH(), scaleX, scaleY, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}
		else {
			image.draw(rp, *hb.get(), win.getW(), win.getH(), scaleX, scaleY, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}

		text.draw(rp, hb->x + posX, hb->y + posY, win.getW(), win.getH());
	}

	void UIToggle::toggle(bool val)
	{
		toggled = val;
		if (onClick) {
			onClick(*this);
		}
	}

	void UIToggle::clickLeftEvent()
	{
		toggle(!toggled);
	}
}