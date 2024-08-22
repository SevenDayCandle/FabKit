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
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image = cct.images.uiCheckboxEmpty, IDrawable& checkImage = cct.images.uiCheckboxFilled, FFont& f = cct.fontRegular(), float xOff = cct.images.uiCheckboxEmpty.getWidth() * 1.15f, float yOff = cct.images.uiCheckboxEmpty.getHeight() * 0.25f):
			UIInteractable(window, move(hb), image), checkImage(checkImage), text(f, text), xOff(xOff), yOff(yOff) {
			UIToggle::onSizeUpdated();
		}

		bool toggled = false;
		IDrawable& checkImage;

		inline float getBeginX() override { return std::min(hb->x, hb->x + text.getPosX()); }
		inline float getBeginY() override { return std::min(hb->y, hb->y + text.getPosY()); }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setTextOffsetX(float xOff) { return this->xOff = xOff, *this; }
		inline UIToggle& setTextOffsetY(float yOff) { return this->yOff = yOff, *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		void onSizeUpdated() override;
		void refreshDimensions() override;
		void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		void toggle(bool val);
	protected:
		TextDrawable text;
	private:
		func<void(UIToggle&)> onClick;
		float xOff = 0;
		float yOff = 0;

		virtual void clickLeftEvent() override;
	};

	void UIToggle::onSizeUpdated()
	{
		text.setPos(cfg.renderScale(xOff), cfg.renderScale(yOff));
	}

	void UIToggle::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		text.reload();
	}

	void UIToggle::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		if (toggled) {
			checkImage.draw(rp, *hb.get(), win.getW(), win.getH(), 1, 1, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}
		else {
			image.draw(rp, *hb.get(), win.getW(), win.getH(), 1, 1, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}

		text.draw(rp, hb->x, hb->y, win.getW(), win.getH());
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