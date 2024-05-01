export module fbc.uiMultiEntry;

import fbc.coreConfig;
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
		virtual ~UIMultiEntry() override {}

		bool toggled = false;
		IDrawable& checkImage;
		IDrawable& uncheckImage;

		inline virtual float getProjectedWidth() override { return uncheckImage.getWidth() + cfg.renderScale(8) + UIText::getTextWidth(); };
		inline virtual void updateSelectStatus(bool selected) override { toggled = selected; };

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
		float textX = check.x + check.w * 1.25f;
		TextInfo::drawText(textX, check.y);
	}
}