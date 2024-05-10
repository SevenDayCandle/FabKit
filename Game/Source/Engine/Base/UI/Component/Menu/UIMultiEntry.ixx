export module fbc.UIMultiEntry;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.IDrawable;
import fbc.FFont;
import fbc.UILabel;
import fbc.FUtil;
import fbc.RelativeHitbox;
import fbc.ScreenManager;
import fbc.UIEntry;
import fbc.FUtil;
import fbc.TextInfo;
import sdl;

export namespace fbc {
	export template <typename T> class UIMultiEntry : public UIEntry<T> {
	public:
		UIMultiEntry(T item, int index, func<void(UIEntry<T>&)> onClick, fbc::RelativeHitbox* hb, FFont& f, const str& text, IDrawable& uncheckImage = cct.images.checkboxEmpty(), IDrawable& checkImage = cct.images.checkboxFilled(), sdl::Color baseColor = sdl::COLOR_WHITE, sdl::Color hoverColor = sdl::COLOR_GOLD):
			UIEntry<T>(item, index, onClick, hb, f, text, baseColor, hoverColor), checkImage(checkImage), uncheckImage(uncheckImage) {
		}
		virtual ~UIMultiEntry() override {}

		bool toggled = false;
		IDrawable& checkImage;
		IDrawable& uncheckImage;

		inline virtual float getProjectedWidth() override { return uncheckImage.getWidth() + cfg.renderScale(8) + UILabel::getTextWidth(); };
		inline virtual void updateSelectStatus(bool selected) override { toggled = selected; };

		virtual void onSizeUpdated() override;
		virtual void renderImpl() override;
	};

	template<typename T>
	void UIMultiEntry<T>::onSizeUpdated()
	{
		TextInfo::setPos(this->hb->h * 1.25f, 0);
	}

	template<typename T> void UIMultiEntry<T>::renderImpl() {

		sdl::RectF check = { this->hb->x, this->hb->y, this->hb->h, this->hb->h };
		if (toggled) {
			checkImage.draw(&check, sdl::COLOR_WHITE);
			if (this->hb->isHovered()) {
				checkImage.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::COLOR_WHITE);
			}
		}
		else {
			uncheckImage.draw(&check, sdl::COLOR_WHITE);
			if (this->hb->isHovered()) {
				uncheckImage.draw(&check, sdl::BlendMode::SDL_BLENDMODE_ADD, sdl::COLOR_WHITE);
			}
		}
		TextInfo::drawText(check.x, check.y);
	}
}