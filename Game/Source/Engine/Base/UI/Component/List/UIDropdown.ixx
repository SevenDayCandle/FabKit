export module fbc.UIDropdown;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UITitledInteractable;
import fbc.IOverlay;
import fbc.ScreenManager;
import fbc.TextInfo;
import fbc.UIEntry;
import fbc.UIInteractable;
import fbc.UISelectorList;
import fbc.ScaleHitbox;
import fbc.SelectView;
import sdl;
import std;

namespace fbc {
	export template <typename T> class UIDropdown : public UITitledInteractable, public TextInfo {
	public:
		UIDropdown(Hitbox* hb, 
			UISelectorList<T>* menu, 
			IDrawable& image = cct.images.uiPanel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(EntryView<T>&)>& buttonLabelFunc = {}
		): UITitledInteractable(hb, image), TextInfo(textFont), menu(menu), buttonLabelFunc(buttonLabelFunc), arrow(arrow), clear(clear) {
			init();
		}
		UIDropdown(Hitbox* hb,
			uptr<UISelectorList<T>> menu,
			IDrawable& image = cct.images.uiPanel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall,
			FFont& textFont = cct.fontRegular(),
			func<str(EntryView<T>&)>& buttonLabelFunc = {}
		): UITitledInteractable(hb, image), TextInfo(textFont), menu(std::move(menu)), buttonLabelFunc(buttonLabelFunc), arrow(arrow), clear(clear) {
			init();
		}

		uptr<UISelectorList<T>> menu;

		inline bool isOpen() const { return proxy != nullptr; }
		inline int selectedSize() const { return menu->selectedSize(); }
		inline int size() { return menu->size(); }
		inline UIDropdown& setItemFont(const FFont& itemFont) { return menu->setItemFont(itemFont), * this; }
		inline UIDropdown& setMaxRows(int rows) { return menu->setMaxRows(rows), * this; }
		inline UIDropdown& setOnChange(const func<void(EntryView<T>&)>& onChange) { return menu->setOnChange(onChange), * this; }
		inline UIDropdown& setOnOpen(const func<void()>& onOpen) { return this->onOpen = onOpen, *this; }
		inline UIDropdown& setSelectionLimit(int rows) { return menu->setSelectionLimit(rows), * this; }
		inline UIDropdown& setSelectionMin(int rows) { return menu->setSelectionMin(rows), * this; }
		inline vec<const T*> getAllItemsAsList() { return menu->toVec(); }
		inline vec<const T*> getSelectedItemsAsList() { return menu->getSelectedItemsAsList(); }
		inline EntryView<T>& getAllItems() { return menu->getAllItems(); }
		inline EntryView<T>& getSelectedItems() { return menu->getSelectedItems(); }
		inline virtual UIDropdown& setOnClose(const func<void()>& onClose) { return this->onClose = onClose, *this; }
		inline void clearItems() { menu->clearItems(); }
		inline void clearSelection() { menu->clearSelection(); }
		inline void selectSingle(T item) { menu->selectSingle(item); }
		inline void selectSingle(T* item) { menu->selectSingle(item); }
		inline void updateSingle(T item) { menu->updateSingle(item); }
		inline void updateSingle(T* item) { menu->updateSingle(item); }
		template <c_itr<int> Iterable> inline void selectIndices(Iterable& indices) { menu->selectIndices(indices); }
		template <c_itr<T> Iterable> inline void selectSelection(Iterable& items) { menu->selectSelection(items); }
		template <c_itr<T*> Iterable> inline void selectSelection(Iterable& items) { menu->selectSelection(items); }
		template <c_varg<T>... Args> inline void selectSelection(Args&&... items) { menu->selectSelection(items); }
		template <c_varg<T*>... Args> inline void selectSelection(Args&&... items) { menu->selectSelection(items); }
		template <c_itr<int> Iterable> inline void updateIndices(Iterable& indices) { menu->updateIndices(indices); }
		template <c_itr<T> Iterable> inline void updateSelection(Iterable& items) { menu->updateSelection(items); }
		template <c_itr<T*> Iterable> inline void updateSelection(Iterable& items) { menu->updateSelection(items); }
		template <c_varg<T>... Args> inline void updateSelection(Args&&... items) { menu->updateSelection(items); }
		template <c_varg<T*>... Args> inline void updateSelection(Args&&... items) { menu->updateSelection(items); }

		template <c_itr<T> Iterable> UIDropdown& addItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIDropdown& addItems(const Iterable& items);
		template <c_varg<T>... Args> UIDropdown& addItems(Args&&... items);
		template <c_varg<T*>... Args> UIDropdown& addItems(Args&&... items);
		template <c_itr<T> Iterable> UIDropdown& setItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIDropdown& setItems(const Iterable& items);
		template <c_varg<T>... Args> UIDropdown& setItems(Args&&... items);
		template <c_varg<T*>... Args> UIDropdown& setItems(Args&&... items);
		void forceClosePopup();
		virtual void onSizeUpdated() override;
		virtual void openPopup();
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void updateImpl() override;
		virtual void unsetProxy();

		static uptr<UIDropdown> multiList(Hitbox* hb, 
			func<str(const T&)> labelFunc = futil::toString<T>,
			func<str(EntryView<T>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.uiDarkPanelRound,
			IDrawable& image = cct.images.uiPanel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
		static uptr<UIDropdown> singleList(Hitbox* hb, 
			func<str(const T&)> labelFunc = futil::toString<T>,
			func<str(EntryView<T>&)> buttonLabelFunc = {},
			FFont& itemFont = cct.fontRegular(),
			FFont& textFont = cct.fontRegular(),
			IDrawable& background = cct.images.uiDarkPanelRound,
			IDrawable& image = cct.images.uiPanel,
			IDrawable& arrow = cct.images.uiArrowSmall,
			IDrawable& clear = cct.images.uiClearSmall);
	protected:
		IDrawable& arrow;
		IDrawable& clear;
		sdl::RectF arrowRect;

		str getButtonText(EntryView<T>& items);
		virtual void clickLeftEvent() override;
		virtual inline void onChangeItems() {}
		virtual void onSelectionUpdate(EntryView<T>& items);
	private:
		func<str(EntryView<T>&)> buttonLabelFunc;
		func<void()> onClose;
		func<void()> onOpen;
		IOverlay* proxy;

		inline bool canClear() { return menu->getMinSelections() < 1; }

		void init();
	};

	export template <typename T> class UIDropdownProxy : public IOverlay {
	public:
		UIDropdownProxy(UIDropdown<T>& menu) : dropdown(menu) {}
		UIDropdown<T>& dropdown;

		void dispose() override;
		void render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		void update() override;
	};

	template<typename T> void UIDropdown<T>::forceClosePopup() {
		if (proxy != nullptr) { screenManager::closeOverlay(proxy); }
	}

	template<typename T> void UIDropdown<T>::refreshDimensions() {
		UITitledInteractable::refreshDimensions();
		refreshCache();
		this->menu->refreshDimensions();
	}

	template<typename T> void UIDropdown<T>::unsetProxy() {
		proxy = nullptr;
		if (onClose) {
			onClose();
		}
	}

	template<typename T> void UIDropdown<T>::onSizeUpdated()
	{
		TextInfo::setPos(cfg.renderScale(24), hb->h * 0.25f);
		arrowRect.w = arrowRect.h = hb->h * 0.5f;
	}

	// When opened, move the menu directly below this button, unless there isn't enough room (in which case it should appear above this button)
	template<typename T> void UIDropdown<T>::openPopup() {
		int bottom = hb->y + hb->h;
		if (bottom + menu->hb->h > cfg.getScreenYSize()) {
			menu->hb->setRealPos(hb->x, hb->y - menu->hb->h);
		}
		else {
			menu->hb->setRealPos(hb->x, bottom);
		}
		if (proxy == nullptr) {
			screenManager::openOverlay(std::make_unique<UIDropdownProxy<T>>(*this));
			proxy = screenManager::getActiveOverlay();
			if (onOpen) {
				onOpen();
			}
		}
	}

	template<typename T> void UIDropdown<T>::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		UITitledInteractable::renderImpl(cd, rp);
		if (this->selectedSize() > 0 && this->canClear()) {
			clear.draw(cd, rp, arrowRect, &this->UIImage::color, rotation);
		}
		else {
			arrow.draw(cd, rp, arrowRect, &this->UIImage::color, menu->isOpen() ? rotation + 180 : rotation);
		}
		TextInfo::drawText(cd, rp, hb->x, hb->y);
	}

	template<typename T> void UIDropdown<T>::updateImpl() {
		UIInteractable::updateImpl();
		arrowRect.x = hb->x + hb->w - arrowRect.w * 1.5f;
		arrowRect.y = hb->y + hb->h * 0.25f;
	}

	// Updates the text shown on the button by default, this may be overriden in derivative types
	template<typename T> void UIDropdown<T>::onSelectionUpdate(EntryView<T>& items) {
		setText(getButtonText(items));
	}

	template<typename T> void UIDropdown<T>::init()
	{
		this->menu->setOnSelectionUpdate([this](EntryView<T>& items) { this->onSelectionUpdate(items); });
		this->menu->hb->setRealPos(hb->x, hb->y);
		UIDropdown<T>::onSizeUpdated();
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::multiList(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UISelectorList<T>::multiList(new ScaleHitbox(hb->getOffSizeX(), hb->getOffSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> uptr<UIDropdown<T>> UIDropdown<T>::singleList(
		Hitbox* hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		return std::make_unique<UIDropdown<T>>(
			hb,
			UISelectorList<T>::singleList(new ScaleHitbox(hb->getOffSizeX(), hb->getOffSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	// The text on the dropdown should reflect the contents of the selected menu items.
	// If no button label function is set, this will default to joining the string representations of each entry. If this text is too long, the displayed text will instead show the number of items selected
	template<typename T> str UIDropdown<T>::getButtonText(EntryView<T>& items)
	{
		if (buttonLabelFunc) {
			return buttonLabelFunc(items);
		}
		else {
			str displayText = (futil::joinStrMap(", ", items, [](UIEntry<T>& entry) {return entry.getText(); }));
			if (this->font.measureW(displayText) > hb->w) {
				return str(cct.strings.ui_items(this->selectedSize()));
			}
			else {
				return displayText;
			}
		}
	}

	// When clicked, open the menu if closed. Otherwise, dispose the menu
	template<typename T> void UIDropdown<T>::clickLeftEvent() {
		if (this->selectedSize() > 0 && sdl::mouseGetX() >= arrowRect.x && this->canClear()) {
			clearSelection();
		}
		else if (isOpen()) {
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

	template<typename T> template<c_itr<T*> Iterable> UIDropdown<T>& UIDropdown<T>::addItems(const Iterable& items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T> ...Args> UIDropdown<T>& UIDropdown<T>::addItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T*> ...Args> UIDropdown<T>& UIDropdown<T>::addItems(Args&&... items)
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

	template<typename T> template<c_itr<T*> Iterable> UIDropdown<T>& UIDropdown<T>::setItems(const Iterable& items)
	{
		this->menu->setItems(items);
		onChangeItems();
		return *this;
	}

	template<typename T> template<c_varg<T> ...Args> UIDropdown<T>& UIDropdown<T>::setItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}


	template<typename T> template<c_varg<T*> ...Args> UIDropdown<T>& UIDropdown<T>::setItems(Args&&... items)
	{
		this->menu->addItems(items);
		onChangeItems();
		return *this;
	}

	/*
	 * UIDropdownProxy Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIDropdownProxy<T>::dispose() { dropdown.unsetProxy(); }

	template<typename T> void UIDropdownProxy<T>::render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		dropdown.menu->renderImpl(cd, rp);
	}

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIDropdownProxy<T>::update() {
		dropdown.updateImpl();
		dropdown.menu->updateImpl();
		if ((sdl::mouseIsLeftJustClicked() && !dropdown.menu->isHovered() && !dropdown.isHovered()) || sdl::keyboardJustPressedEsc()) { screenManager::closeOverlay(this); }
	}

}