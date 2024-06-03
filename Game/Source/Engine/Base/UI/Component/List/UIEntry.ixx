export module fbc.UIEntry;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.TextInfo;
import fbc.IDrawable;
import fbc.UIInteractable;
import fbc.UILabel;
import fbc.FUtil;
import fbc.RelativeHitbox;
import fbc.ScreenManager;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UIEntry : public UIInteractable, public TextInfo {
	public:
		UIEntry(const T& item, int index, func<void(UIEntry<T>&)> onClick, fbc::RelativeHitbox* hb, FFont& f, const str& text, IDrawable& image = cct.images.uiCheckboxEmpty, IDrawable& checkImage = cct.images.uiCheckboxFilled, sdl::Color baseColor = sdl::COLOR_WHITE, sdl::Color hoverColor = sdl::COLOR_GOLD) :
			item(item), index(index), onClick(onClick), baseColor(baseColor), hoverColor(hoverColor), UIInteractable(hb, image), TextInfo(f, text), checkImage(checkImage) {
		}
		virtual ~UIEntry() override {}

		sdl::Color baseColor;
		sdl::Color hoverColor;
		bool toggled = false;
		IDrawable& checkImage;
		func<void(UIEntry<T>&)> onClick;
		const T& item;
		int index;

		inline virtual float getProjectedWidth() { return image.getWidth() + cfg.renderScale(8) + TextInfo::getTextWidth(); };
		inline virtual void updateSelectStatus(bool selected) { toggled = selected; };

		virtual void onSizeUpdated() override;
		virtual void refreshRenderables() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		inline virtual void clickLeftEvent() override { onClick(*this); }
	};

	template<typename T> void UIEntry<T>::onSizeUpdated()
	{
		TextInfo::setPos(this->hb->h * 1.25f, 0);
	}

	template<typename T> void UIEntry<T>::refreshRenderables()
	{
		UIInteractable::refreshRenderables();
		updateCache();
	}

	template<typename T> void UIEntry<T>::renderImpl() {

		sdl::RectF check = { this->hb->x, this->hb->y, this->hb->h, this->hb->h };
		if (toggled) {
			checkImage.draw(&check, sdl::COLOR_WHITE);
			if (this->hb->isHovered()) {
				checkImage.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::COLOR_WHITE);
			}
		}
		else {
			image.draw(&check, sdl::COLOR_WHITE);
			if (this->hb->isHovered()) {
				image.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::COLOR_WHITE);
			}
		}
		TextInfo::drawText(check.x, check.y);
	}

	// When hovered, change the text color
	template<typename T> void UIEntry<T>::updateImpl() {
		UIInteractable::updateImpl();
		if (hb->justHovered()) {
			TextInfo::setColor(hoverColor);
		}
		else if (hb->justUnhovered()) {
			TextInfo::setColor(baseColor);
		}
	}
}