export module fbc.UISelectorList;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.IOverlay;
import fbc.RelativeHitbox;
import fbc.ScreenManager;
import fbc.UIBase;
import fbc.UIEntry;
import fbc.UIList;
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import sdl;
import std;

constexpr int MARGIN = 16;

export namespace fbc {
	export template <typename T> class UISelectorList : public UIList<T> {

	public:
		UISelectorList(Hitbox* hb,
		       func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
		       FFont& itemFont = cct.fontRegular(),
		       IDrawable& background = cct.images.panelRound,
		       bool canAutosize = false):
			UIList<T>(hb, labelFunc, itemFont, background, canAutosize),
			scrollbar(new RelativeHitbox(*hb, 0, 0, 48, 48)) { scrollbar.setOnScroll([this](float f) { onScroll(f); }); }

		~UISelectorList() override {}

		inline bool isOpen() const { return proxy != nullptr; }
		inline UISelectorList& setFilterFunc(func<bool(const UIEntry<T>*)> filterFunc) { return this->filterFunc = filterFunc, *this; }
		inline UISelectorList& setItemFont(FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UISelectorList& setLabelFunc(func<const str(T&)> labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UISelectorList& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), *this; }
		inline UISelectorList& setOnChange(func<void(vec<const T*>)> onChange) { return this->onChange = onChange, *this; }
		inline UISelectorList& setOnClose(func<void()> onClose) { return this->onClose = onClose, *this; }
		inline UISelectorList& setOnOpen(func<void()> onOpen) { return this->onOpen = onOpen, *this; }
		inline UISelectorList& setOnSelectionUpdate(func<void(vec<const UIEntry<T>*>&)> onSelectionUpdate) {return this->onSelectionUpdate = onSelectionUpdate, *this;}

		inline int selectedSize() const { return currentIndices.size(); }

		UISelectorList& setSelectionLimit(int rows);
		vec<const T*> getSelectedItems();
		void clearSelection();
		void forceClosePopup();
		void openPopup();
		void refilterRows();
		void refreshDimensions() override;
		void renderImpl() override;
		template <c_itr<int> Iterable> void selectIndices(Iterable& indices);
		template <c_itr<T> Iterable> void selectSelection(Iterable& items);
		template <c_itr<T*> Iterable> void selectSelection(Iterable& items);
		template <c_varg<T>... Args> void selectSelection(Args&&... items);
		template <c_varg<T*>... Args> void selectSelection(Args&&... items);
		void selectSingle(T item);
		void selectSingle(T* item);
		void selectRow(UIEntry<T>& entry) override;
		void unsetProxy();
		void updateImpl() override;
		template <c_itr<int> Iterable> void updateIndices(Iterable& indices);
		template <c_itr<T> Iterable> void updateSelection(Iterable& indices);
		template <c_itr<T*> Iterable> void updateSelection(Iterable& indices);
		template <c_varg<T>... Args> void updateSelection(Args&&... items);
		template <c_varg<T*>... Args> void updateSelection(Args&&... items);
		void updateSingle(T item);
		void updateSingle(T* item);

		static uptr<UISelectorList> multiMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.darkPanelRound, bool canAutosize = false);
		static uptr<UISelectorList> singleMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.darkPanelRound, bool canAutosize = false);
	protected:
		set<int> currentIndices;
		vec<UIEntry<T>*> rowsForRender;

		inline int getVisibleRowCount() const { return std::min(static_cast<int>(rowsForRender.size()), this->maxRows); }
	private:
		int selectionLimit = std::numeric_limits<int>::max();
		func<bool(const UIEntry<T>*)> filterFunc;
		func<void(vec<const T*>)> onChange;
		func<void()> onClose;
		func<void()> onOpen;
		func<void(vec<const UIEntry<T>*>&)> onSelectionUpdate;
		UIVerticalScrollbar scrollbar;
		IOverlay* proxy;

		inline static float rMargin() { return cfg.renderScale(MARGIN); }

		void autosize() override;
		void changeEvent();
		void onScroll(float percent);
		void refreshRows() override;
		void syncRowsForRender();
		void updateForSelection();
		void updateRowPositions();
	};

	export template <typename T> class UIMenuProxy : public IOverlay {
	public:
		UIMenuProxy(UISelectorList<T>& menu) : menu(menu) {}
		UISelectorList<T>& menu;

		inline void render() override { menu.renderImpl(); };

		void dispose() override;
		void update() override;
	};

	// Updates the selected indexes. DOES invoke the change callback.
	template <typename T> template <c_itr<int> Iterable> void UISelectorList<T>::selectIndices(Iterable& indices) {
		updateIndices(indices);
		changeEvent();
	}


	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template <typename T> template <c_itr<T> Iterable> void UISelectorList<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template <typename T> template <c_itr<T*> Iterable> void UISelectorList<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template<typename T> template<c_varg<T> ...Args> void UISelectorList<T>::selectSelection(Args&&... items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template<typename T> template<c_varg<T*> ...Args> void UISelectorList<T>::selectSelection(Args&&... items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given item. DOES invoke the change callback.
	template<typename T> void UISelectorList<T>::selectSingle(T item) {
		updateSingle(item);
		changeEvent();
	}

	// Updates the selected indexes based on the given item. DOES invoke the change callback.
	template<typename T> void UISelectorList<T>::selectSingle(T* item) {
		updateSingle(item);
		changeEvent();
	}

	// Updates the selected indexes. Does NOT invoke the change callback.
	template <typename T> template <c_itr<int> Iterable> void UISelectorList<T>::updateIndices(Iterable& indices) {
		currentIndices.clear();
		currentIndices.insert(indices.begin(), indices.end());
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable> void UISelectorList<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			opt<T> res = futil::find(items, row->item);
			if (res != std::nullopt) { currentIndices.insert(row->index); }
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback.
	template <typename T> template <c_itr<T*> Iterable> void UISelectorList<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			opt<T> res = futil::find(items, &row->item);
			if (res != std::nullopt) { currentIndices.insert(row->index); }
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items (varargs version). Does NOT invoke the change callback.
	template<typename T> template<c_varg<T> ...Args> void UISelectorList<T>::updateSelection(Args&&... items)
	{
		uset<T*> set{ std::forward<Args>(items)... };
		updateSelection(set);
	}

	// Updates the selected indexes based on the given items (varargs version). Does NOT invoke the change callback.
	template<typename T> template<c_varg<T*> ...Args> void UISelectorList<T>::updateSelection(Args&&... items)
	{
		uset<T*> set{ std::forward<Args>(items)... };
		updateSelection(set);
	}

	// Updates the selected indexes based on the given single item. Does NOT invoke the change callback.
	template<typename T> void UISelectorList<T>::updateSingle(T item)
	{
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (item == row->item) {
				currentIndices.insert(row->index);
			}
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given single item. Does NOT invoke the change callback.
	template<typename T> void UISelectorList<T>::updateSingle(T* item)
	{
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (item == &row->item) {
				currentIndices.insert(row->index);
			}
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Change the maximum number of rows that can be selected. If there were previously more selected rows than this limit, prunes off rows to meet the selection limit
	template<typename T> UISelectorList<T>& UISelectorList<T>::setSelectionLimit(int rows)
	{
		this->selectionLimit = std::clamp(rows, 0, std::numeric_limits<int>::max());
		return *this;
	}

	// Unselects all items. DOES invoke the change callback
	template <typename T> void UISelectorList<T>::clearSelection() {
		currentIndices.clear();
		changeEvent();
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Manually take down the overlay spawned by this menu
	template <typename T> void UISelectorList<T>::forceClosePopup() {
		if (proxy != nullptr) { screenManager::closeOverlay(proxy); }
	}

	// Returns the entries corresponding with the currently selected indices
	template <typename T> vec<const T*> UISelectorList<T>::getSelectedItems() {
		vec<const T*> items;
		for (int i : currentIndices) { items.push_back(&(this->rows[i]->item)); }
		return items;
	}

	// Create a proxy overlay for this menu that closes when you click outside of it
	template <typename T> void UISelectorList<T>::openPopup() {
		if (proxy == nullptr) {
			screenManager::openOverlay(std::make_unique<UIMenuProxy<T>>(*this));
			proxy = screenManager::getActiveOverlay();
			if (onOpen) {
				onOpen();
			}
		}
	}

	// Forcibly apply the filter function on the rows and update their positions
	template<typename T> void UISelectorList<T>::refilterRows()
	{
		syncRowsForRender();
		updateRowPositions();
	}

	// Updates the dimensions of all children too
	template<typename T> void UISelectorList<T>::refreshDimensions() {
		UIList<T>::refreshDimensions();
		scrollbar.refreshDimensions();
	}

	// Render all visible rows and the scrollbar if it is shown
	template <typename T> void UISelectorList<T>::renderImpl() {
		this->background.draw(this->hb.get(), this->backgroundColor, {0, 0}, 0, sdl::FlipMode::SDL_FLIP_NONE);
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->renderImpl();
		}

		scrollbar.render();
	}

	// Update visible rows. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UISelectorList<T>::updateImpl() {
		UIBase::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) { rowsForRender[i]->updateImpl(); }

		scrollbar.update();

		// TODO handle keyboard/controllers
	}

	// If the row exists in the selection, remove it. Otherwise, add it to the selection. Invokes the change callback
	template <typename T> void UISelectorList<T>::selectRow(UIEntry<T>& entry) {
		if (currentIndices.contains(entry.index)) {
			currentIndices.erase(entry.index);
			entry.updateSelectStatus(false);
		}
		else {
			if (currentIndices.size() >= selectionLimit) {
				UIEntry<T>* first = this->rows[*currentIndices.begin()].get();
				first->updateSelectStatus(false);
				currentIndices.erase(first->index);
			}
			currentIndices.insert(entry.index);
			entry.updateSelectStatus(true);
		}
		changeEvent();
		updateForSelection();
	}

	// Detach the popup proxy and call the dispose callback
	template<typename T>
	void UISelectorList<T>::unsetProxy() {
		proxy = nullptr;
		if (onClose) {
			onClose();
		}
	}

	// Whenever the items contained in the menu change, we need to update the rows that will actually be rendered on the screen with the underlying rows
	// If there's a filter function defined, use it to filter out the available rows to render.
	// Then, make the scrollbar active if the number of rows exceeds the number of rows that can be shown at once
	template <typename T> void UISelectorList<T>::syncRowsForRender() {
		if (filterFunc) {
			rowsForRender.clear();
			for (const uptr<UIEntry<T>>& row : this->rows) {
				UIEntry<T>* entry = row.get();
				if (filterFunc(entry)) {
					rowsForRender.push_back(entry);
				}
			}
		}
		else {
			rowsForRender.resize(this->rows.size());
			std::transform(this->rows.begin(), this->rows.end(), rowsForRender.begin(),
				[](const uptr<UIEntry<T>>& entry) { return entry.get(); });
		}

		scrollbar.enabled = rowsForRender.size() > this->maxRows;
	}

	// When the items are changed, the rows should be expanded to match the width of the longest projected row if autosizing is enabled. Otherwise, they should match the existing hitbox width minus the scrollbar width
	// The scrollbar should be placed immediately to the right of the items, and it should be expanded vertically to cover all the rows
	// The menu should be expanded to cover the rows as well as the scrollbar
	template <typename T>
	void UISelectorList<T>::autosize() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float sizeY = rowCount * (this->rows.size() > 0 ? this->rows[0]->hb->h : 0);
		if (this->canAutosize) {
			float maxWidth = std::transform_reduce(this->rows.begin(), this->rows.end(), 0,
			                                       [](float a, float b) { return std::max(a, b); },
			                                       [](const uptr<UIEntry<T>>& row) {
				                                       return row->getProjectedWidth();
			                                       });
			for (const uptr<UIEntry<T>>& row : this->rows) { row->setHbExactSizeX(maxWidth); }

			scrollbar.hb->setExactPos(this->hb->x + maxWidth + rMarg, this->hb->y + rMarg);
			scrollbar.setHbExactSizeY(sizeY);
			this->setHbExactSize(maxWidth + scrollbar.hb->w, sizeY + rMarg * 2);
		}
		else {
			float targetWidth = this->hb->w - scrollbar.hb->w - rMarg;
			for (const uptr<UIEntry<T>>& row : this->rows) {
				row->setHbExactSizeX(targetWidth);
			}

			scrollbar.hb->setExactPos(this->hb->x + targetWidth, this->hb->y + rMarg);
			scrollbar.setHbExactSizeY(sizeY);
			this->setHbExactSizeY(sizeY + rMarg * 2);
		}

		updateRowPositions();
	}

	template<typename T> void UISelectorList<T>::changeEvent() {
		if (onChange) {
			onChange(getSelectedItems());
		}
	}

	// Whenever the scrollbar position changes, we should update the top visible row and row positions
	template <typename T> void UISelectorList<T>::onScroll(float percent) {
		int limit = rowsForRender.size() - getVisibleRowCount();
		int newIndex = std::clamp(static_cast<int>(percent * limit), 0, limit);
		if (newIndex != this->topVisibleRowIndex) {
			this->topVisibleRowIndex = newIndex;
			updateRowPositions();
		}
	}

	// When the rows are changed, reposition the rows and sort them, and clear out your current selection because it will likely no longer be valid
	template<typename T> void UISelectorList<T>::refreshRows() {
		currentIndices.clear();
		syncRowsForRender();
		autosize();
		updateForSelection();
	}

	// Hook used to update dropdowns to update their display strings
	template <typename T> void UISelectorList<T>::updateForSelection() {
		if (onSelectionUpdate) {
			vec<const UIEntry<T>*> items;
			for (int i : currentIndices) { items.push_back(this->rows[i].get()); }
			onSelectionUpdate(items);
		}
	}

	// Whenever the scrollbar position is changed or items are changed, we need to update the positions of each row
	template <typename T> void UISelectorList<T>::updateRowPositions() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float x = this->hb->x + rMarg;
		float y = this->hb->y + rMarg;
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->hb->setExactPos(x, y);
			y += rowsForRender[i]->hb->h;
		}
	}

	/*
	 * Statics
	 */

	template<typename T> uptr<UISelectorList<T>> UISelectorList<T>::multiMenu(Hitbox* hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize) {
		return std::make_unique<UISelectorList<T>>(hb, labelFunc, itemFont, background, canAutosize);
	}

	template<typename T> uptr<UISelectorList<T>> UISelectorList<T>::singleMenu(Hitbox* hb,
		func<str(const T&)> labelFunc,
		FFont& itemFont,
		IDrawable& background, 
		bool canAutosize) {
		uptr<UISelectorList<T>> res = std::make_unique<UISelectorList<T>>(hb, labelFunc, itemFont, background, canAutosize);
		res->setSelectionLimit(1);
		return res;
	}
	/*
	 * UIMenuProxy Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIMenuProxy<T>::dispose() { menu.unsetProxy(); }

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIMenuProxy<T>::update() {
		menu.updateImpl();
		if ((sdl::mouseIsLeftJustClicked() && !menu.isHovered()) || sdl::keyboardJustPressedEsc()) { screenManager::closeOverlay(this); }
	}
}
