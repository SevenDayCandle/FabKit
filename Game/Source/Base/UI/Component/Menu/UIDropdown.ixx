export module fbc.uiDropdown;

import fbc.coreConfig;
import fbc.coreContent;
import fbc.ffont;
import fbc.futil;
import fbc.hitbox;
import fbc.iDrawable;
import fbc.screenManager;
import fbc.textInfo;
import fbc.uiEntry;
import fbc.uiImage;
import fbc.uiMenu;
import fbc.scaleHitbox;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UIDropdown : public UIImage, public TextInfo {
	public:

		UIDropdown(Hitbox* hb, 
			UIMenu<T>* menu, 
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(), 
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		): UIImage(hb, image), TextInfo(textFont), menu(menu), buttonLabelFunc(buttonLabelFunc), arrow(arrow) {
			this->menu->setOnSelectionUpdate([this](vec<UIEntry<T>*> items) { this->onSelectionUpdate(std::move(items)); });
		}
		UIDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {}
		): UIImage(hb, image), TextInfo(textFont), menu(std::move(menu)), buttonLabelFunc(buttonLabelFunc), arrow(arrow) {
			this->menu->setOnSelectionUpdate([this](vec<UIEntry<T>*> items) { this->onSelectionUpdate(std::move(items)); });
		}
		virtual ~UIDropdown() override{}

		bool interactable = true;
		uptr<UIMenu<T>> menu;
		IDrawable* arrow;

		inline void clearItems() { menu->clearItems(); }
		inline bool isOpen() { return menu->isOpen(); }
		inline UIDropdown& setEntryFunc(func<UIEntry<T>*(UIMenu<T>&, T&, str&, int)> entryFunc) { return menu->setEntryFunc(entryFunc), *this; }
		inline UIDropdown& setOnChange(func<void(vec<T*>&)> onChange) { return menu->setOnChange(onChange), * this; }
		inline UIDropdown& setOnClose(func<void(vec<T*>&)> onClose) { return menu->setOnClose(onClose), * this; }
		inline UIDropdown& setOnOpen(func<void(vec<T*>&)> onOpen) { return menu->setOpen(onOpen), * this; }
		inline int size() { return menu->size(); }
		inline UIDropdown& setItemFont(FFont& itemFont) { return menu->setItemFont(itemFont), * this; }
		inline UIDropdown& setMaxRows(int rows) { return menu->setMaxRows(rows), * this; }
		inline vec<T*> getAllItems() { return menu->getAllItems(); }
		inline vec<T*> getSelectedItems() { return menu->getSelectedItems(); }
		inline void clearSelection() { menu->clearSelection(); }
		inline void forceClosePopup() { menu->forceClosePopup(); }
		template <c_itr<T> Iterable> inline UIDropdown& addItems(Iterable& items) { return menu->addItems(items), *this; }
		template <c_itr<T> Iterable> inline UIDropdown& setItems(Iterable& items) { return menu->setItems(items), *this; }
		template <c_itr<int> Iterable> inline void selectIndices(Iterable& indices) { return menu->selectIndices(indices), *this; }
		template <c_itr<T> Iterable> inline void selectSelection(Iterable& items) { return menu->selectSelection(items), *this; }
		template <c_itr<int> Iterable> inline void updateIndices(Iterable& indices) { return menu->updateIndices(indices), *this; }
		template <c_itr<T> Iterable> inline void updateSelection(Iterable& indices) { return menu->updateSelection(indices), *this; }

		void openPopup();
		void renderImpl() override;
		void updateImpl() override;

		static uptr<UIDropdown> multiMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
		static uptr<UIDropdown> singleMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
	private:
		func<str(vec<UIEntry<T>*>)> buttonLabelFunc;

		void onSelectionUpdate(vec<UIEntry<T>*> items);
	};



	// When opened, move the menu directly below this button, unless there isn't enough room (in which case it should appear above this button)
	template<typename T> void UIDropdown<T>::openPopup() {
		int bottom = hb->y + hb->h;
		if (bottom + menu->hb->h > cfg.getScreenYSize()) {
			menu->hb->move(hb->x, hb->y - menu->hb->h);
		}
		else {
			menu->hb->move(hb->x, bottom);
		}
		menu->openPopup();
	}

	template<typename T> void UIDropdown<T>::renderImpl() {
		UIImage::renderImpl();
		if (arrow) {
			float w = arrow->getWidth();
			sdl::RectF arrowRect = { hb->x + hb->w - w * 1.5f, hb->y + hb->h * 0.25f, w, arrow->getHeight()};
			arrow->draw(&arrowRect, UIImage::color, origin, rotation, menu->isOpen() ? sdl::RendererFlip::SDL_FLIP_VERTICAL : flip);
		}
		float textX = hb->x + cfg.renderScale(8);
		float textY = hb->y + hb->h * 0.25f;
		TextInfo::drawText(hb->x, textY);
	}

	// When clicked, open the menu if not open. Otherwise, close it
	template<typename T> void UIDropdown<T>::updateImpl()
	{
		UIImage::updateImpl();

		if (hb->isHovered()) {
			if (screenManager::activeElement == nullptr && interactable) {
				if (hb->isJust()) {
					// TODO play sound
				}

				if (sdl::mouseIsLeftJustClicked()) {
					screenManager::activeElement = this;
				}
			}
			else if (screenManager::activeElement == this && sdl::mouseIsLeftJustReleased()) {
				if (menu->isOpen()) {
					menu->forceClosePopup();
				}
				else {
					openPopup();
				}

				screenManager::activeElement = nullptr;
			}
		}
		else if (screenManager::activeElement == this && (sdl::mouseIsLeftJustReleased())) {
			screenManager::activeElement = nullptr;
		}
	}

	// The text on the dropdown should reflect the contents of the selected menu items.
	// If no button label function is set, this will default to joining the string representations of each entry. If this text is too long, the displayed text will instead show the number of items selected
	template<typename T> void UIDropdown<T>::onSelectionUpdate(vec<UIEntry<T>*> items) {
		if (buttonLabelFunc) {
			setText(buttonLabelFunc(std::move(items)));
		}
		else {
			setText(futil::joinStrMap(", ", items, [](UIEntry<T>* entry) {return entry->getText(); }));
			if (getTextWidth() > hb->w) {
				
			}
		}
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::multiMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UIMenu<T>::multiMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::singleMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UIMenu<T>::singleMenu(new ScaleHitbox(hb->getOffsetSizeX(), hb->getOffsetSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			textFont,
			buttonLabelFunc
		);
	}

}