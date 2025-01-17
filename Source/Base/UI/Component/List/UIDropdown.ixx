export module fab.UIDropdown;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.ScaleHitbox;
import fab.SelectView;
import fab.TextDrawable;
import fab.UIEntry;
import fab.UIInteractable;
import fab.UISelectorList;
import fab.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLRunner;
import std;

namespace fab {
	export template <typename T> class UIDropdown : public UIInteractable {
	public:
		UIDropdown(FWindow& window, uptr<Hitbox>&& hb, uptr<UISelectorList<T>> menu,
			IDrawable& image, IDrawable& arrow, IDrawable& clear,
			FFont& textFont, func<str(EntryView<T>&)>& buttonLabelFunc = {}) :
			UIInteractable(window, move(hb), image), text(textFont),
			menu(move(menu)), buttonLabelFunc(buttonLabelFunc), arrow(arrow), clear(clear) {
			init();
		}
		UIDropdown(FWindow& window, uptr<Hitbox>&& hb, uptr<UISelectorList<T>> menu, func<str(EntryView<T>&)>& buttonLabelFunc = {}) :
			UIDropdown(window, move(hb), move(menu),
				window.props.defaultPanel(), window.props.defaultArrowSmall(), window.props.defaultClear(),
				window.props.fontRegular(), buttonLabelFunc) {}
		UIDropdown(UIDropdown&& other) noexcept : UIInteractable(other.win, move(other.hb), *other.image), text(move(other.text)), menu(move(other.menu)), buttonLabelFunc(move(other.buttonLabelFunc)), arrow(other.arrow), clear(other.clear) {
			init();
		};

		uptr<UISelectorList<T>> menu;

		inline bool isOpen() const { return proxy != nullptr; }
		inline int selectedSize() const { return menu->selectedSize(); }
		inline int size() { return menu->size(); }
		inline UIDropdown& setItemFont(const FFont& itemFont) { return menu->setItemFont(itemFont), * this; }
		inline UIDropdown& setMaxRows(int rows) { return menu->setMaxRows(rows), * this; }
		inline UIDropdown& setOnChange(const func<void(EntryView<T>&)>& onChange) { return menu->setOnChange(onChange), * this; }
		inline UIDropdown& setOnChange(func<void(EntryView<T>&)>&& onChange) { return menu->setOnChange(move(onChange)), * this; }
		inline UIDropdown& setOnOpen(const func<void()>& onOpen) { return this->onOpen = onOpen, *this; }
		inline UIDropdown& setOnOpen(func<void()>&& onOpen) { return this->onOpen = move(onOpen), *this; }
		inline UIDropdown& setSelectionLimit(int rows) { return menu->setSelectionLimit(rows), * this; }
		inline UIDropdown& setSelectionMin(int rows) { return menu->setSelectionMin(rows), * this; }
		inline vec<const T*> getAllItemsAsList() { return menu->toVec(); }
		inline vec<const T*> getSelectedItemsAsList() { return menu->getSelectedItemsAsList(); }
		inline EntryView<T>& getAllItems() { return menu->getAllItems(); }
		inline EntryView<T>& getSelectedItems() { return menu->getSelectedItems(); }
		inline UIDropdown& setOnClose(const func<void()>& onClose) { return this->onClose = onClose, *this; }
		inline UIDropdown& setOnClose(func<void()>&& onClose) { return this->onClose = move(onClose), *this; }
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
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
		virtual void unsetProxy();

		inline static UIDropdown multiList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, func<str(EntryView<T>&)> buttonLabelFunc = {}) {
			return multiList(window, std::move(hb), labelFunc, buttonLabelFunc, window.props.fontRegular(), window.props.fontRegular(), window.props.defaultBackground(), window.props.defaultButton(), window.props.defaultArrowSmall(), window.props.defaultClear());
		}

		inline static UIDropdown singleList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, func<str(EntryView<T>&)> buttonLabelFunc = {}) {
			return singleList(window, std::move(hb), labelFunc, buttonLabelFunc, window.props.fontRegular(), window.props.fontRegular(), window.props.defaultBackground(), window.props.defaultButton(), window.props.defaultArrowSmall(), window.props.defaultClear());
		}

		static UIDropdown multiList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear);
		static UIDropdown singleList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear);

	protected:
		IDrawable& arrow;
		IDrawable& clear;
		sdl::RectF arrowRect;
		TextDrawable text;

		str getButtonText(EntryView<T>& items);
		virtual void clickLeftEvent() override;
		virtual inline void onChangeItems() {}
		virtual void onSelectionUpdate(EntryView<T>& items);
	private:
		func<str(EntryView<T>&)> buttonLabelFunc;
		func<void()> onClose;
		func<void()> onOpen;
		FWindow::Element* proxy;

		inline bool canClear() { return menu->getMinSelections() < 1; }

		void init();
	};

	export template <typename T> class UIDropdownProxy : public FWindow::Element {
	public:
		UIDropdownProxy(FWindow& window, UIDropdown<T>& menu) : Element(window), dropdown(menu) {}
		UIDropdown<T>& dropdown;

		void dispose() override;
		void render(sdl::SDLBatchRenderPass& rp) override;
		void update() override;
	};

	template<typename T> void UIDropdown<T>::forceClosePopup() {
		if (proxy != nullptr) { this->win.closeOverlay(proxy); }
	}

	template<typename T> void UIDropdown<T>::refreshDimensions() {
		UIInteractable::refreshDimensions();
		text.reload();
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
		arrowRect.w = arrowRect.h = hb->h * 0.5f;
	}

	// When opened, move the menu directly below this button, unless there isn't enough room (in which case it should appear above this button)
	template<typename T> void UIDropdown<T>::openPopup() {
		int bottom = hb->y + hb->h;
		if (bottom + menu->hb->h > win.getH()) {
			menu->hb->setRealPos(hb->x, hb->y - menu->hb->h);
		}
		else {
			menu->hb->setRealPos(hb->x, bottom);
		}
		menu->updateImpl(); // Update to update menu sub-hitboxes
		if (proxy == nullptr) {
			this->win.openOverlay(std::make_unique<UIDropdownProxy<T>>(this->win, *this));
			proxy = this->win.getActiveOverlay();
			if (onOpen) {
				onOpen();
			}
		}
	}

	template<typename T> void UIDropdown<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {
		UIInteractable::renderImpl(rp);
		if (this->selectedSize() > 0 && this->canClear()) {
			clear.draw(rp, arrowRect, win.getW(), win.getH(), scaleX, scaleY, rotation, &this->UIImage::color);
		}
		else {
			arrow.draw(rp, arrowRect, win.getW(), win.getH(), scaleX, menu->isOpen() ? -scaleY : scaleY, rotation, &this->UIImage::color);
		}
		text.draw(rp, hb->x + win.renderScale(24), hb->y + hb->h * 0.25f, win.getW(), win.getH());
	}

	template<typename T> void UIDropdown<T>::updateImpl() {
		UIInteractable::updateImpl();
		arrowRect.x = hb->x + hb->w - arrowRect.w * 1.5f;
		arrowRect.y = hb->y + hb->h * 0.25f;
	}

	// Updates the text shown on the button by default, this may be overriden in derivative types
	template<typename T> void UIDropdown<T>::onSelectionUpdate(EntryView<T>& items) {
		this->text.setText(getButtonText(items));
	}

	template<typename T> void UIDropdown<T>::init()
	{
		this->menu->setOnSelectionUpdate([this](EntryView<T>& items) { this->onSelectionUpdate(items); });
		this->menu->hb->setRealPos(hb->x, hb->y);
		UIDropdown<T>::onSizeUpdated();
	}

	template<typename T> UIDropdown<T> UIDropdown<T>::multiList(
		FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		Hitbox& ref = *hb;
		return UIDropdown<T>(
			window,
			move(hb),
			UISelectorList<T>::multiList(window, make_unique<ScaleHitbox>(window, ref.getOffSizeX(), ref.getOffSizeY()), labelFunc, itemFont, background),
			image,
			arrow,
			clear,
			textFont,
			buttonLabelFunc
		);
	}

	template<typename T> UIDropdown<T> UIDropdown<T>::singleList(
		FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, func<str(EntryView<T>&)> buttonLabelFunc, FFont& itemFont, FFont& textFont, IDrawable& background, IDrawable& image, IDrawable& arrow, IDrawable& clear)
	{
		Hitbox& ref = *hb;
		return UIDropdown<T>(
			window,
			move(hb),
			UISelectorList<T>::singleList(window, make_unique<ScaleHitbox>(window, ref.getOffSizeX(), ref.getOffSizeY()), labelFunc, itemFont, background),
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
			return (futil::joinStrMap(", ", items, [](UIEntry<T>& entry) {return entry.getText(); }));
		}
	}

	// When clicked, open the menu if closed. Otherwise, dispose the menu
	template<typename T> void UIDropdown<T>::clickLeftEvent() {
		if (this->selectedSize() > 0 && sdl::runner::mouseGetX() >= arrowRect.x && this->canClear()) {
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

	template<typename T> void UIDropdownProxy<T>::render(sdl::SDLBatchRenderPass& rp) {
		dropdown.menu->renderImpl(rp);
	}

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIDropdownProxy<T>::update() {
		dropdown.updateImpl();
		dropdown.menu->updateImpl();
		if ((sdl::runner::mouseIsLeftJustClicked() && !dropdown.menu->isHovered() && !dropdown.isHovered()) || sdl::runner::keyboardJustPressedEsc()) { this->win.closeOverlay(this); }
	}

}