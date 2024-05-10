export module fbc.UIEntry;

import fbc.CoreConfig;
import fbc.FFont;
import fbc.UILabel;
import fbc.FUtil;
import fbc.RelativeHitbox;
import fbc.ScreenManager;
import sdl;

export namespace fbc {
	export template <typename T> class UIEntry : public UILabel {
	public:
		UIEntry(T item, int index, func<void(UIEntry<T>&)> onClick, fbc::RelativeHitbox* hb, FFont& f, const str& text, sdl::Color baseColor = sdl::COLOR_WHITE, sdl::Color hoverColor = sdl::COLOR_GOLD):
			item(item), index(index), onClick(onClick), baseColor(baseColor), hoverColor(hoverColor), UILabel(hb, f, text) {
		}
		virtual ~UIEntry() override {}

		sdl::Color baseColor;
		sdl::Color hoverColor;
		func<void(UIEntry<T>&)> onClick;
		T item;
		int index;

		inline virtual float getProjectedWidth() { return getTextWidth(); };
		inline virtual void updateSelectStatus(bool selected) {};

		virtual void updateImpl() override;
	};

	// When hovered, change the text color
	template<typename T> void UIEntry<T>::updateImpl() {
		UILabel::updateImpl();
		if (hb->justHovered()) {
			setColor(hoverColor);
		}
		else if (hb->justUnhovered()) {
			setColor(baseColor);
		}

		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && sdl::mouseIsLeftJustClicked()) {
				screenManager::activeElement = this;
			}
			else if (screenManager::activeElement == this && sdl::mouseIsLeftJustReleased()) {
				onClick(*this);
				screenManager::activeElement = nullptr;
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}
}