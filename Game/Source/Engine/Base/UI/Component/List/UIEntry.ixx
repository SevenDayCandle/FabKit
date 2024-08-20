export module fbc.UIEntry;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FWindow;
import fbc.TextDrawable;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.UILabel;
import fbc.FUtil;
import fbc.RelativeHitbox;
import sdl;
import std;

namespace fbc {
	export template <typename T> class UIEntry : public UIInteractable {
	public:
		UIEntry(const T& item, int index, const func<void(UIEntry<T>&)>& onClick, FWindow& window, RelativeHitbox* hb, FFont& f, const str& text, IDrawable& image = cct.images.uiCheckboxEmpty, IDrawable& checkImage = cct.images.uiCheckboxFilled, sdl::Color baseColor = sdl::COLOR_STANDARD, sdl::Color hoverColor = sdl::COLOR_STANDARD) :
			UIInteractable(window, hb, image), item(item), index(index), onClick(onClick), baseColor(baseColor), hoverColor(hoverColor), text(f, text), checkImage(checkImage) {
		}

		operator const T*() const { return &item; }
		operator const T&() const { return item; }

		bool active = false;
		bool toggled = false;
		const T& item;
		int index;

		inline strv getText() { return text.getText(); }
		inline virtual float getProjectedWidth() { return image.getWidth() + cfg.renderScale(8) + text.getWidth(); };
		inline virtual void updateActiveStatus(bool val) { active = val; };
		inline virtual void updateSelectStatus(bool selected) { toggled = selected; };

		virtual void onHbHover();
		virtual void onHbUnhover();
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	protected:
		sdl::Color baseColor;
		sdl::Color hoverColor;
		IDrawable& checkImage;
		func<void(UIEntry<T>&)> onClick;
		TextDrawable text;

		inline virtual void clickLeftEvent() override { onClick(*this); }
	};

	template<typename T> void UIEntry<T>::onHbHover()
	{
		text.setColor(hoverColor);
	}

	template<typename T> void UIEntry<T>::onHbUnhover()
	{
		text.setColor(baseColor);
	}

	template<typename T> void UIEntry<T>::onSizeUpdated()
	{
		text.setPos(this->hb->h * 1.25f, 0);
	}

	template<typename T> void UIEntry<T>::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		text.reload();
	}

	template<typename T> void UIEntry<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {
		if (active) {
			if (toggled) {
				checkImage.draw(rp, this->hb->x, this->hb->y, this->hb->h, this->hb->h, win.getW(), win.getH(), 0, &sdl::COLOR_WHITE);
			}
			else {
				image.draw(rp, this->hb->x, this->hb->y, this->hb->h, this->hb->h, win.getW(), win.getH(), 0, &sdl::COLOR_WHITE);
			}
		}
		else {
			if (toggled) {
				checkImage.draw(rp, this->hb->x, this->hb->y, this->hb->h, this->hb->h, win.getW(), win.getH());
			}
			else {
				image.draw(rp, this->hb->x, this->hb->y, this->hb->h, this->hb->h, win.getW(), win.getH());
			}
		}

		text.draw(rp, this->hb->x, this->hb->y, win.getW(), win.getH());
	}
}