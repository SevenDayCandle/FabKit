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
	export template <typename T> class UIEntry : public UIInteractable, public TextDrawable {
	public:
		UIEntry(const T& item, int index, const func<void(UIEntry<T>&)>& onClick, FWindow& window, RelativeHitbox* hb, FFont& f, const str& text, IDrawable& image = cct.images.uiCheckboxEmpty, IDrawable& checkImage = cct.images.uiCheckboxFilled, sdl::Color baseColor = sdl::COLOR_STANDARD, sdl::Color hoverColor = sdl::COLOR_STANDARD) :
			item(item), index(index), onClick(onClick), baseColor(baseColor), hoverColor(hoverColor), UIInteractable(window, hb, image), TextDrawable(f, text), checkImage(checkImage) {
		}

		operator const T*() const { return &item; }
		operator const T&() const { return item; }

		bool active = false;
		bool toggled = false;
		const T& item;
		int index;

		inline virtual float getProjectedWidth() { return image.getWidth() + cfg.renderScale(8) + TextDrawable::getTextWidth(); };
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

		inline virtual void clickLeftEvent() override { onClick(*this); }
	};

	template<typename T> void UIEntry<T>::onHbHover()
	{
		TextDrawable::setColor(hoverColor);
	}

	template<typename T> void UIEntry<T>::onHbUnhover()
	{
		TextDrawable::setColor(baseColor);
	}

	template<typename T> void UIEntry<T>::onSizeUpdated()
	{
		TextDrawable::setPos(this->hb->h * 1.25f, 0);
	}

	template<typename T> void UIEntry<T>::refreshDimensions()
	{
		UIInteractable::refreshDimensions();
		refreshCache();
	}

	template<typename T> void UIEntry<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {

		sdl::RectF check = { this->hb->x, this->hb->y, this->hb->h, this->hb->h };


		if (active) {
			if (toggled) {
				checkImage.draw(rp, check, win.getW(), win.getH(), 0, &sdl::COLOR_WHITE);
			}
			else {
				image.draw(rp, check, win.getW(), win.getH(), 0, &sdl::COLOR_WHITE);
			}
		}
		else {
			if (toggled) {
				checkImage.draw(rp, check, win.getW(), win.getH());
			}
			else {
				image.draw(rp, check, win.getW(), win.getH());
			}
		}

		TextDrawable::drawText(rp, check.x, check.y, win.getW(), win.getH());
	}
}