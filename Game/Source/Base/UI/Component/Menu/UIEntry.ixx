export module fbc.uiEntry;

import fbc.coreConfig;
import fbc.ffont;
import fbc.uiText;
import fbc.futil;
import fbc.relativeHitbox;
import fbc.screenManager;
import sdl;

export namespace fbc {
	export template <typename T> class UIEntry : public UIText {
	public:
		UIEntry(T item, int index, func<void(UIEntry<T>&)> onClick, fbc::RelativeHitbox* hb, FFont& f, const str& text, sdl::Color baseColor = sdl::COLOR_WHITE, sdl::Color hoverColor = sdl::COLOR_GOLD):
			item(item), index(index), onClick(onClick), baseColor(baseColor), hoverColor(hoverColor), UIText(hb, f, text) {
			hb->setExactSizeY(getProjectedHeight());
		}
		virtual ~UIEntry() override {}

		sdl::Color baseColor;
		sdl::Color hoverColor;
		func<void(UIEntry<T>&)> onClick;
		T item;
		int index;

		inline virtual float getProjectedHeight() { return cfg.renderScale(64); };
		inline virtual float getProjectedWidth() { return getTextWidth(); };
		inline virtual void updateSelectStatus(bool selected) {};

		virtual void updateImpl() override;
	};

	// When hovered, change the text color
	template<typename T> void UIEntry<T>::updateImpl() {
		UIText::updateImpl();
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