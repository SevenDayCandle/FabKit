export module fab.UIToggle;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.TextDrawable;
import fab.UIInteractable;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UIToggle : public UIInteractable {
	public:
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f, float xOff, float yOff) :
			UIInteractable(window, move(hb), image), checkImage(&checkImage), text(f, text), offX(xOff), offY(yOff) {
			UIToggle::onSizeUpdated();
		}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f, float xOff) :
			UIToggle(window, move(hb), text, image, checkImage, f, xOff, image.getHeight() * 0.25f) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage, FFont& f) :
			UIToggle(window, move(hb), text, image, checkImage, f,
				image.getWidth() * 1.15f, image.getHeight() * 0.25f) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text, IDrawable& image, IDrawable& checkImage) :
			UIToggle(window, move(hb), text, image, checkImage, window.props.fontRegular()) {}
		UIToggle(FWindow& window, uptr<Hitbox>&& hb, strv text) :
			UIToggle(window, move(hb), text, window.props.defaultCheckboxEmpty(), window.props.defaultCheckboxFilled(), window.props.fontRegular()) {}

		bool toggled = false;
		IDrawable* checkImage;

		inline float getBeginX() override { return std::min(hb->x, hb->x + posX); }
		inline float getBeginY() override { return std::min(hb->y, hb->y + posY); }
		inline UIToggle& setCheckImage(IDrawable& checkImage) { return this->checkImage = &checkImage, *this; }
		inline UIToggle& setCheckImage(IDrawable* checkImage) { return this->checkImage = checkImage, *this; }
		inline UIToggle& setOnClick(const func<void(UIToggle&)>& onClick) { return this->onClick = onClick, *this; }
		inline UIToggle& setOnClick(func<void(UIToggle&)>&& onClick) { return this->onClick = move(onClick), *this; }
		inline UIToggle& setToggleState(bool val) { return this->toggled = val, *this; }

		UIToggle& setTextOffset(float xOff, float yOff);
		void onSizeUpdated() override;
		void refreshDimensions() override;
		void renderImpl(BatchRenderPass& rp) override;
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
		this->posX = win.renderScale(offX);
		this->posY = win.renderScale(offY);
	}

	void UIToggle::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		text.reload();
	}

	void UIToggle::renderImpl(BatchRenderPass& rp) {
		if (toggled) {
			checkImage->draw(rp, *hb.get(), scaleX, scaleY, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}
		else {
			image->draw(rp, *hb.get(), scaleX, scaleY, rotation, hb->isHovered() ? &sdl::COLOR_WHITE : &this->UIImage::color);
		}

		text.drawFull(rp, hb->x + posX, hb->y + posY);
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