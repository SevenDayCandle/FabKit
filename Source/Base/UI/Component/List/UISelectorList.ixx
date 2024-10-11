export module fbc.UISelectorList;

import fbc.FFont;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.FWindow;
import fbc.RelativeHitbox;
import fbc.SelectView;
import fbc.UIBase;
import fbc.UIEntry;
import fbc.UIList;
import fbc.UIVerticalScrollbar;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	constexpr int MARGIN = 16;

	export template <typename T> class UISelectorList : public UIList<T> {
	public:
		UISelectorList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize = false) :
			UIList<T>(window, move(hb), move(labelFunc), itemFont, background, canAutosize),
			scrollbar(window, make_unique<RelativeHitbox>(window, *this->hb, 0, 0, 48, 48)) {
			scrollbar.setOnScroll([this](float f) { onScroll(f); });
		}
		UISelectorList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, bool canAutosize = false) :
			UISelectorList(window, move(hb), move(labelFunc), window.props.fontSmall(), window.props.defaultPanel(), canAutosize) {}
		UISelectorList(UISelectorList&& other) noexcept = default;

		~UISelectorList() override {}

		inline auto getSelectedItems() { return std::views::transform(currentIndices, [this](int i) { return &(this->rows[i]->item); }); }
		inline bool isOpen() const { return proxy != nullptr; }
		inline UISelectorList& setFilterFunc(const func<bool(const UIEntry<T>*)>& filterFunc) { return this->filterFunc = filterFunc, *this; }
		inline UISelectorList& setFilterFunc(func<bool(const UIEntry<T>*)>&& filterFunc) { return this->filterFunc = move(filterFunc), *this; }
		inline UISelectorList& setItemFont(const FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UISelectorList& setLabelFunc(const func<str(const T&)>& labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UISelectorList& setLabelFunc(func<str(const T&)>&& labelFunc) { return UIList<T>::setLabelFunc(move(labelFunc)), * this; }
		inline UISelectorList& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), *this; }
		inline UISelectorList& setOnChange(const func<void(EntryView<T>&)>& onChange) { return this->onChange = onChange, *this; }
		inline UISelectorList& setOnChange(func<void(EntryView<T>&)>&& onChange) { return this->onChange = move(onChange), *this; }
		inline UISelectorList& setOnClose(const func<void()>& onClose) { return this->onClose = onClose, *this; }
		inline UISelectorList& setOnClose(func<void()>&& onClose) { return this->onClose = move(onClose), *this; }
		inline UISelectorList& setOnOpen(const func<void()>& onOpen) { return this->onOpen = onOpen, *this; }
		inline UISelectorList& setOnOpen(func<void()>&& onOpen) { return this->onOpen = move(onOpen), *this; }
		inline UISelectorList& setOnSelectionUpdate(const func<void(EntryView<T>&)>& onSelectionUpdate) {return this->onSelectionUpdate = onSelectionUpdate, *this;}
		inline UISelectorList& setOnSelectionUpdate(func<void(EntryView<T>&)>&& onSelectionUpdate) { return this->onSelectionUpdate = move(onSelectionUpdate), *this; }

		inline int getMinSelections() const { return selectionMin; }
		inline int selectedSize() const { return static_cast<int>(currentIndices.size()); }

		UISelectorList& setSelectionLimit(int rows);
		UISelectorList& setSelectionMin(int rows);
		vec<const T*> getSelectedItemsAsList();
		void clearSelection();
		void forceClosePopup();
		void openPopup();
		void refilterRows();
		void refreshDimensions() override;
		void renderImpl(sdl::SDLBatchRenderPass& rp) override;
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

		inline static uptr<UISelectorList> multiList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, bool canAutosize = false) {
			return multiList(window, std::move(hb), labelFunc, window.props.fontSmall(), window.props.defaultBackground(), canAutosize);
		}
		inline static uptr<UISelectorList> singleList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, bool canAutosize = false) {
			return singleList(window, std::move(hb), labelFunc, window.props.fontSmall(), window.props.defaultBackground(), canAutosize);
		}

		static uptr<UISelectorList> multiList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize = false);
		static uptr<UISelectorList> singleList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize = false);
	protected:
		set<int> currentIndices;
		vec<UIEntry<T>*> rowsForRender;

		inline int getVisibleRowCount() const { return std::min(static_cast<int>(rowsForRender.size()), this->maxRows); }

		virtual void updateTopVisibleRowIndex(int value) override;
	private:
		int selectionLimit = std::numeric_limits<int>::max();
		int selectionMin = 0;
		func<bool(const UIEntry<T>*)> filterFunc;
		func<void()> onClose;
		func<void()> onOpen;
		func<void(EntryView<T>&)> onChange;
		func<void(EntryView<T>&)> onSelectionUpdate;
		UIVerticalScrollbar scrollbar;
		FWindow::Element* proxy;

		inline EntryView<T> selectView() { return EntryView<T>(currentIndices, this->rows); }
		inline float rMargin() { return this->win.renderScale(MARGIN); }

		void autosize() override;
		void changeEvent();
		void onScroll(float percent);
		void refreshRows() override;
		void syncRowsForRender();
		void updateForSelection();
		void updateRowPositions();
	};

	export template <typename T> class UIMenuProxy : public FWindow::Element {
	public:
		UIMenuProxy(FWindow& window, UISelectorList<T>& menu) : Element(window), menu(menu) {}
		UISelectorList<T>& menu;

		inline void render(sdl::SDLBatchRenderPass& rp) override { menu.renderImpl(&rp); };

		void dispose() override;
		void update() override;
	};

	// Updates the selected indexes. DOES invoke the change callback. Note that this does not enforce selection limits.
	template <typename T> template <c_itr<int> Iterable> void UISelectorList<T>::selectIndices(Iterable& indices) {
		updateIndices(indices);
		changeEvent();
	}


	// Updates the selected indexes based on the given items. DOES invoke the change callback. Note that this does not enforce selection limits.
	template <typename T> template <c_itr<T> Iterable> void UISelectorList<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback. Note that this does not enforce selection limits.
	template <typename T> template <c_itr<T*> Iterable> void UISelectorList<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> template<c_varg<T> ...Args> void UISelectorList<T>::selectSelection(Args&&... items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> template<c_varg<T*> ...Args> void UISelectorList<T>::selectSelection(Args&&... items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes based on the given item. DOES invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> void UISelectorList<T>::selectSingle(T item) {
		updateSingle(item);
		changeEvent();
	}

	// Updates the selected indexes based on the given item. DOES invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> void UISelectorList<T>::selectSingle(T* item) {
		updateSingle(item);
		changeEvent();
	}

	// Updates the selected indexes. Does NOT invoke the change callback. Note that this does not enforce selection limits.
	template <typename T> template <c_itr<int> Iterable> void UISelectorList<T>::updateIndices(Iterable& indices) {
		currentIndices.clear();
		currentIndices.insert(indices.begin(), indices.end());
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback. Note that this does not enforce selection limits.
	template <typename T> template <c_itr<T> Iterable> void UISelectorList<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (futil::has(items, row->item)) { currentIndices.insert(row->index); }
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback. Note that this does not enforce selection limits
	template <typename T> template <c_itr<T*> Iterable> void UISelectorList<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (futil::has(items, row->item)) { currentIndices.insert(row->index); }
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items (varargs version). Does NOT invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> template<c_varg<T> ...Args> void UISelectorList<T>::updateSelection(Args&&... items)
	{
		uset<T*> set{ std::forward<Args>(items)... };
		updateSelection(set);
	}

	// Updates the selected indexes based on the given items (varargs version). Does NOT invoke the change callback. Note that this does not enforce selection limits.
	template<typename T> template<c_varg<T*> ...Args> void UISelectorList<T>::updateSelection(Args&&... items)
	{
		uset<T*> set{ std::forward<Args>(items)... };
		updateSelection(set);
	}

	// Updates the selected indexes based on the given single item. Does NOT invoke the change callback. Note that this does not enforce selection limits.
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

	// Updates the selected indexes based on the given single item. Does NOT invoke the change callback. Note that this does not enforce selection limits.
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
		int ind = 0;
		while (this->selectedSize() > this->selectionLimit && ind < this->size()) {
			if (this->currentIndices.contains(ind)) {
				selectRow(*(this->rows[ind]));
			}
			++ind;
		}
		return *this;
	}

	// Enforce a minimum number of rows to be selected. If the current selection is below the minimum, select rows from top to bottom until the requirements are met
	template<typename T> UISelectorList<T>& UISelectorList<T>::setSelectionMin(int rows)
	{
		this->selectionMin = rows;
		int ind = 0;
		while (this->selectedSize() < this->selectionMin && ind < this->size()) {
			if (!this->currentIndices.contains(ind)) {
				selectRow(*(this->rows[ind]));
			}
			++ind;
		}
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
		if (proxy != nullptr) { this->win.closeOverlay(proxy); }
	}

	// Returns the entries corresponding with the currently selected indices
	template <typename T> vec<const T*> UISelectorList<T>::getSelectedItemsAsList() {
		vec<const T*> items(currentIndices.size());
		for (int i : currentIndices) { items.push_back(&(this->rows[i]->item)); }
		return items;
	}

	// Create a proxy overlay for this menu that closes when you click outside of it
	template <typename T> void UISelectorList<T>::openPopup() {
		if (proxy == nullptr) {
			this->win.openOverlay(std::make_unique<UIMenuProxy<T>>(*this));
			proxy = this->win.getActiveOverlay();
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
	template <typename T> void UISelectorList<T>::renderImpl(sdl::SDLBatchRenderPass& rp) {
		this->background.draw(rp, *this->hb.get(), this->win.getW(), this->win.getH(), 1, 1, 0, &this->backgroundColor);
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->renderImpl(rp);
		}

		scrollbar.render(rp);
	}

	// Update visible rows. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UISelectorList<T>::updateImpl() {
		UIBase::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->updateImpl();
			if (rowsForRender[i]->hb->justHovered()) {
				this->activeRow = i;
			}
		}

		if (this->activeRow >= 0) {
			if (this->win.props.hasPressedDirUp()) {
				this->activeRow = std::max(0, this->activeRow - 1);
				if (this->activeRow < this->topVisibleRowIndex) {
					updateTopVisibleRowIndex(this->topVisibleRowIndex - 1);
					updateRowPositions();
				}
			}
			else if (this->win.props.hasPressedDirDown()) {
				this->activeRow = std::min(static_cast<int>(rowsForRender.size()) - 1, this->activeRow + 1);
				if (this->activeRow >= this->topVisibleRowIndex + this->maxRows) {
					updateTopVisibleRowIndex(this->topVisibleRowIndex + 1);
					updateRowPositions();
				}
			}
			else if (sdl::runner::mouseIsLeftJustClicked() && !this->isHovered()) {
				this->activeRow = -1;
			}
		}

		scrollbar.update();
		scrollbar.processMouseScroll();

		for (int i = 0; i < rowsForRender.size(); ++i) {
			rowsForRender[i]->updateActiveStatus(this->activeRow == i);
		}

		if (this->activeRow >= 0 && this->win.props.hasPressedSelect()) {
			this->selectRow(*rowsForRender[this->activeRow]);
		}
	}

	// If the row exists in the selection, remove it. Otherwise, add it to the selection. Invokes the change callback
	template <typename T> void UISelectorList<T>::selectRow(UIEntry<T>& entry) {
		if (currentIndices.contains(entry.index)) {
			if (currentIndices.size() > selectionMin) {
				currentIndices.erase(entry.index);
				entry.updateSelectStatus(false);
			}
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
		float sizeY = rowCount * (this->rows.size() > 0 ? this->rows[0]->hb->h : 0.0);
		if (this->canAutosize) {
			float maxWidth = std::transform_reduce(this->rows.begin(), this->rows.end(), 0.0,
			                                       [](float a, float b) { return std::max(a, b); },
			                                       [](const uptr<UIEntry<T>>& row) {
				                                       return row->getProjectedWidth();
			                                       });
			for (const uptr<UIEntry<T>>& row : this->rows) { row->setHbExactSizeX(maxWidth); }

			scrollbar.hb->setRealPos(this->hb->x + maxWidth + rMarg, this->hb->y + rMarg);
			scrollbar.setHbExactSizeY(sizeY);
			this->setHbExactSize(maxWidth + scrollbar.hb->w, sizeY + rMarg * 2);
		}
		else {
			float targetWidth = this->hb->w - scrollbar.hb->w - rMarg;
			for (const uptr<UIEntry<T>>& row : this->rows) {
				row->setHbExactSizeX(targetWidth);
			}

			scrollbar.hb->setRealPos(this->hb->x + targetWidth, this->hb->y + rMarg);
			scrollbar.setHbExactSizeY(sizeY);
			this->setHbExactSizeY(sizeY + rMarg * 2);
		}

		updateRowPositions();
	}

	template<typename T> void UISelectorList<T>::changeEvent() {
		if (onChange) {
			SelectView view = this->selectView();
			onChange(view);
		}
	}

	// Whenever the scrollbar position changes, we should update the top visible row and row positions
	template <typename T> void UISelectorList<T>::onScroll(float percent) {
		int limit = static_cast<int>(rowsForRender.size()) - getVisibleRowCount();
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
			SelectView view = this->selectView();
			onSelectionUpdate(view);
		}
	}

	// Whenever the scrollbar position is changed or items are changed, we need to update the positions of each row
	template <typename T> void UISelectorList<T>::updateRowPositions() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float x = this->hb->x + rMarg;
		float y = this->hb->y + rMarg;
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->hb->setRealPos(x, y);
			y += rowsForRender[i]->hb->h;
		}
	}

	/*
	 * Statics
	 */

	template<typename T> uptr<UISelectorList<T>> UISelectorList<T>::multiList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize) {
		return std::make_unique<UISelectorList<T>>(window, move(hb), labelFunc, itemFont, background, canAutosize);
	}

	template<typename T> uptr<UISelectorList<T>> UISelectorList<T>::singleList(FWindow& window, uptr<Hitbox>&& hb,
		func<str(const T&)> labelFunc,
		FFont& itemFont,
		IDrawable& background, 
		bool canAutosize) {
		uptr<UISelectorList<T>> res = std::make_unique<UISelectorList<T>>(window, move(hb), labelFunc, itemFont, background, canAutosize);
		res->setSelectionLimit(1);
		return res;
	}

	template<typename T> void UISelectorList<T>::updateTopVisibleRowIndex(int value)
	{
		UIList<T>::updateTopVisibleRowIndex(value);
		int count = static_cast<int>(rowsForRender.size()) - getVisibleRowCount();
		scrollbar.setScrollPos(count > 0 ? value / static_cast<float>(count) : 0);
	}

	/*
	 * UIMenuProxy Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIMenuProxy<T>::dispose() { menu.unsetProxy(); }

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIMenuProxy<T>::update() {
		menu.updateImpl();
		if ((sdl::runner::mouseIsLeftJustClicked() && !menu.isHovered()) || sdl::runner::keyboardJustPressedEsc()) { this->win.closeOverlay(this); }
	}
}
