export module fbc.uiMultiEntry;

import fbc.coreContent;
import fbc.iDrawable;
import fbc.ffont;
import fbc.uiText;
import fbc.futil;
import fbc.relativeHitbox;
import fbc.screenManager;
import fbc.uiEntry;
import fbc.futil;
import fbc.textInfo;
import sdl;

export namespace fbc {
	export template <typename T> class UIMultiEntry : public UIEntry<T> {
	public:
		UIMultiEntry(T item, int index, func<void(UIEntry<T>&)> onClick, fbc::RelativeHitbox* hb, FFont& f, const str& text, IDrawable& uncheckImage = cct.images.checkboxEmpty(), IDrawable& checkImage = cct.images.checkboxFilled(), sdl::Color baseColor = sdl::WHITE, sdl::Color hoverColor = sdl::GOLD):
			UIEntry<T>(item, index, onClick, hb, f, text, baseColor, hoverColor), checkImage(checkImage), uncheckImage(uncheckImage) {}
		virtual ~UIMultiEntry() {}

		bool toggled = false;
		IDrawable& checkImage;
		IDrawable& uncheckImage;

		inline virtual float getProjectedWidthOffset() override { return uncheckImage.getWidth() + 8 + UIText::getTextWidth(); };

		virtual void renderImpl() override;
	};

	template<typename T> void UIMultiEntry<T>::renderImpl() {

		sdl::RectF check = { this->hb->x, this->hb->y, this->hb->h, this->hb->h };
		if (toggled) {
			checkImage.draw(&check, sdl::WHITE);
			if (this->hb->isHovered()) {
				checkImage.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::WHITE);
			}
		}
		else {
			uncheckImage.draw(&check, sdl::WHITE);
			if (this->hb->isHovered()) {
				uncheckImage.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::WHITE);
			}
		}
		float textX = check.x + check.w * 1.5f;
		float textY = check.y + check.h * 0.5f;
		TextInfo::drawText(textX, textY);
	}
}