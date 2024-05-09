export module fbc.UIDropdown;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.ScreenManager;
import fbc.TextInfo;
import fbc.UIEntry;
import fbc.UIInteractable;
import fbc.UIMenu;
import fbc.ScaleHitbox;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UIDropdown : public UIInteractable, public TextInfo {
	public:

		UIDropdown(Hitbox* hb, 
			UIMenu<T>* menu, 
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(), 
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>&)> buttonLabelFunc = {}
		): UIInteractable(hb, image), TextInfo(textFont), menu(menu), buttonLabelFunc(buttonLabelFunc), arrow(arrow) {
			this->menu->setOnSelectionUpdate([this](vec<UIEntry<T>*>& items) { this->onSelectionUpdate(items); });
		}
		UIDropdown(Hitbox* hb,
			uptr<UIMenu<T>> menu,
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall(),
			FFont& textFont = cct.fontRegular(),
			func<str(vec<UIEntry<T>*>&)> buttonLabelFunc = {}
		): UIInteractable(hb, image), TextInfo(textFont), menu(std::move(menu)), buttonLabelFunc(buttonLabelFunc), arrow(arrow) {
			this->menu->setOnSelectionUpdate([this](vec<UIEntry<T>*>& items) { this->onSelectionUpdate(items); });
		}
		virtual ~UIDropdown() override{}

		uptr<UIMenu<T>> menu;
		IDrawable* arrow;

		inline void clearItems() { menu->clearItems(); }
		inline bool isOpen() { return menu->isOpen(); }
		inline int selectedSize() const { return menu->selectedSize(); }
		inline UIDropdown& setEntryFunc(func<UIEntry<T>*(UIMenu<T>&, T&, str&, int)> entryFunc) { return menu->setEntryFunc(entryFunc), *this; }
		inline UIDropdown& setOnChange(func<void(vec<T*>&)> onChange) { return menu->setOnChange(onChange), * this; }
		inline virtual UIDropdown& setOnClose(func<void()> onClose) { return menu->setOnClose(onClose), * this; }
		inline UIDropdown& setOnOpen(func<void()> onOpen) { return menu->setOpen(onOpen), * this; }
		inline int size() { return menu->size(); }
		inline UIDropdown& setItemFont(FFont& itemFont) { return menu->setItemFont(itemFont), * this; }
		inline UIDropdown& setMaxRows(int rows) { return menu->setMaxRows(rows), * this; }
		inline vec<T*> getAllItems() { return menu->getAllItems(); }
		inline vec<T*> getSelectedItems() { return menu->getSelectedItems(); }
		inline void clearSelection() { menu->clearSelection(); }
		inline void forceClosePopup() { menu->forceClosePopup(); }
		template <c_itr<int> Iterable> inline void selectIndices(Iterable& indices) { return menu->selectIndices(indices), *this; }
		template <c_itr<T> Iterable> inline void selectSelection(Iterable& items) { return menu->selectSelection(items), *this; }
		template <c_itr<int> Iterable> inline void updateIndices(Iterable& indices) { return menu->updateIndices(indices), *this; }
		template <c_itr<T> Iterable> inline void updateSelection(Iterable& indices) { return menu->updateSelection(indices), *this; }

		template <c_itr<T> Iterable> UIDropdown& addItems(const Iterable& items);
		template <c_itr<T> Iterable> UIDropdown& setItems(const Iterable& items);
	
		virtual void openPopup();
		virtual void renderImpl() override;

		static uptr<UIDropdown> multiMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
		static uptr<UIDropdown> singleMenu(Hitbox* hb, 
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			func<str(vec<UIEntry<T>*>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.flatPanel(),
			IDrawable& image = cct.images.smallPanel(),
			IDrawable* arrow = &cct.images.arrowSmall());
	protected:
		str getButtonText(vec<UIEntry<T>*>& items);

		virtual void clickLeftEvent() override;
		virtual inline void onChangeItems() {}
		virtual void onSelectionUpdate(vec<UIEntry<T>*>& items);
	private:
		func<str(vec<UIEntry<T>*>&)> buttonLabelFunc;
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
		UIInteractable::renderImpl();
		if (arrow) {
			float w = arrow->getWidth();
			sdl::RectF arrowRect = { hb->x + hb->w - w * 1.5f, hb->y + hb->h * 0.25f, w, arrow->getHeight()};
			arrow->draw(&arrowRect, UIImage::color, origin, rotation, menu->isOpen() ? sdl::FlipMode::SDL_FLIP_VERTICAL : flip);
		}
		float textX = hb->x + cfg.renderScale(24);
		float textY = hb->y + hb->h * 0.25f;
		TextInfo::drawText(textX, textY);
	}

	// Updates the text shown on the button by default, this may be overriden in derivative types
	template<typename T> void UIDropdown<T>::onSelectionUpdate(vec<UIEntry<T>*>& items) {
		setText(getButtonText(items));
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::multiMenu(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
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
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(vec<UIEntry<T>*>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable* arrow)
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

	// The text on the dropdown should reflect the contents of the selected menu items.
	// If no button label function is set, this will default to joining the string representations of each entry. If this text is too long, the displayed text will instead show the number of items selected
	template<typename T> str UIDropdown<T>::getButtonText(vec<UIEntry<T>*>& items)
	{
		if (buttonLabelFunc) {
			return buttonLabelFunc(items);
		}
		else {
			str displayText = (futil::joinStrMap(", ", items, [](UIEntry<T>* entry) {return entry->getText(); }));
			if (this->font.measureW(displayText) > hb->w) {
				return cct.strings.ui_items(this->selectedSize());
			}
			else {
				return displayText;
			}
		}
	}

	// When clicked, open the menu if closed. Otherwise, close the menu
	template<typename T> void UIDropdown<T>::clickLeftEvent() {
		if (menu->isOpen()) {
			menu->forceClosePopup();
		}
		else {
			openPopup();
		}
	}

	template<typename T> template<c_itr<T> Iterable> UIDropdown<T>& UIDropdown<T>::addItems(const Iterable& items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_itr<T> Iterable> UIDropdown<T>& UIDropdown<T>::setItems(const Iterable& items)
	{
		this->menu->setItems(items);
		onChangeItems();
		return *this;
	}

}