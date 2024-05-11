export module fbc.UIMenu;

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
import fbc.UIBase;
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import sdl;
import std;

constexpr int MARGIN = 16;

export namespace fbc {
	export template <typename T> class UIMenu : public UIBase {
		using FuncEntry = func<UIEntry<T>*(UIMenu&, T&, str&, int)>;

	public:
		UIMenu(Hitbox* hb,
		       FuncEntry entryFunc,
		       func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
		       FFont& itemFont = cct.fontRegular(),
		       IDrawable& background = cct.images.flatPanel()):
			UIBase(hb), background(background), itemFont(itemFont), entryFunc(entryFunc), labelFunc(labelFunc),
			scrollbar(new RelativeHitbox(*hb, 0, 0, 48, 48)) { scrollbar.setOnScroll([this](float f) { onScroll(f); }); }

		~UIMenu() override {}

		sdl::Color backgroundColor = sdl::COLOR_WHITE;
		IDrawable& background;

		inline void clearItems() { setItems(); }
		inline FFont& getItemFont() const { return itemFont; }
		inline bool isOpen() const { return proxy != nullptr; }
		inline UIMenu& setFilterFunc(func<bool(UIEntry<T>*)> filterFunc) { return this->filterFunc = filterFunc, *this; }
		inline UIMenu& setOnChange(func<void(vec<T*>)> onChange) { return this->onChange = onChange, *this; }
		inline UIMenu& setOnClose(func<void()> onClose) { return this->onClose = onClose, *this; }
		inline UIMenu& setOnOpen(func<void()> onOpen) { return this->onOpen = onOpen, *this; }

		inline UIMenu& setOnSelectionUpdate(func<void(vec<UIEntry<T>*>&)> onSelectionUpdate) {
			return this->onSelectionUpdate = onSelectionUpdate, *this;
		}

		inline int selectedSize() const { return currentIndices.size(); }
		inline int size() const { return rows.size(); }

		template <c_itr<T> Iterable> UIMenu& addItems(Iterable& items);
		template <c_itr<T> Iterable> UIMenu& setItems(Iterable& items);
		UIMenu& setEntryFunc(FuncEntry entryFunc);
		UIMenu& setHeaderRow(uptr<UIBase>&& headerRow);
		UIMenu& setItemFont(FFont& itemFont);
		UIMenu& setLabelFunc(func<const str(T&)> labelFunc);
		UIMenu& setMaxRows(int rows);
		vec<T*> getAllItems();
		vec<T*> getSelectedItems();
		void clearSelection();
		void forceClosePopup();
		void openPopup();
		void refilterRows();
		void refreshHb() override;
		void renderImpl() override;
		template <c_itr<int> Iterable> void selectIndices(Iterable& indices);
		template <c_itr<T> Iterable> void selectSelection(Iterable& items);
		void selectSingleRow(UIEntry<T>& entry);
		void toggleRow(UIEntry<T>& entry);
		void unsetProxy();
		void updateImpl() override;
		template <c_itr<int> Iterable> void updateIndices(Iterable& indices);
		template <c_itr<T> Iterable> void updateSelection(Iterable& indices);

		static uptr<UIMenu> multiMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.flatPanel());
		static uptr<UIMenu> singleMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.flatPanel());
	protected:
		FFont& itemFont = cct.fontRegular();
		FuncEntry entryFunc;
		func<const str(T&)> labelFunc;
		set<int> currentIndices;
		vec<uptr<UIEntry<T>>> rows;
		vec<UIEntry<T>*> rowsForRender;

		inline int getVisibleRowCount() const { return std::min(static_cast<int>(rowsForRender.size()), maxRows); }

		void makeRow(T item);

	private:
		bool canAutosize;
		int maxRows = 15;
		int topVisibleRowIndex;
		func<bool(UIEntry<T>*)> filterFunc;
		func<void(vec<T*>)> onChange;
		func<void()> onClose;
		func<void()> onOpen;
		func<void(vec<UIEntry<T>*>&)> onSelectionUpdate;
		uptr<UIBase> headerRow;
		UIVerticalScrollbar scrollbar;
		IOverlay* proxy;

		inline static float rMargin() { return cfg.renderScale(MARGIN); }

		void autosize();
		void onScroll(float percent);
		void syncRowsForRender();
		void updateForSelection();
		void updateRowPositions();
	};

	export template <typename T> class UIMenuProxy : public IOverlay {
	public:
		UIMenuProxy(UIMenu<T>& menu) : menu(menu) {}
		UIMenu<T>& menu;

		inline void render() override { menu.renderImpl(); };

		void close() override;
		void update() override;
	};

	export template <typename T> UIEntry<T>* multiSelectFunc(UIMenu<T>& menu, T& item, str& name, int index);
	export template <typename T> UIEntry<T>* singleSelectFunc(UIMenu<T>& menu, T& item, str& name, int index);


	// Create rows for each item in the provided list
	template <typename T> template <c_itr<T> Iterable>
	UIMenu<T>& UIMenu<T>::addItems(Iterable& items) {
		for (const T item : items) { makeRow(item); }
		syncRowsForRender();
		autosize();
		updateForSelection();
		return *this;
	}

	// Replaces the current rows with rows for each item in the provided list. Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable>
	UIMenu<T>& UIMenu<T>::setItems(Iterable& items) {
		currentIndices.clear();
		rows.clear();
		topVisibleRowIndex = 0;
		return addItems(items);
	}

	// Updates the selected indexes. DOES invoke the change callback.
	template <typename T> template <c_itr<int> Iterable>
	void UIMenu<T>::selectIndices(Iterable& indices) {
		updateIndices(indices);
		if (onChange) { onChange(getSelectedItems()); }
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template <typename T> template <c_itr<T> Iterable>
	void UIMenu<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		if (onChange) { onChange(getSelectedItems()); }
	}

	// Updates the selected indexes. Does NOT invoke the change callback.
	template <typename T> template <c_itr<int> Iterable>
	void UIMenu<T>::updateIndices(Iterable& indices) {
		currentIndices.clear();
		currentIndices.insert(indices.begin(), indices.end());
		for (const uptr<UIEntry<T>>& row : rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable>
	void UIMenu<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : rows) {
			opt<T> res = futil::find(items, row->item);
			if (res != std::nullopt) { currentIndices.insert(row.index); }
		}
		for (const uptr<UIEntry<T>>& row : rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the entry generation function and regenerates all existing rows with it
	template <typename T> UIMenu<T>& UIMenu<T>::setEntryFunc(FuncEntry entryFunc) {
		vec<uptr<UIEntry<T>>> originalItems = std::move(rows);
		rows.clear();
		for (const uptr<UIEntry<T>>& row : rows) { makeRow(row.item); }
		syncRowsForRender();
		autosize();
		return *this;
	}

	// Updates the header row. This will resize the menu as necessary
	template <typename T> UIMenu<T>& UIMenu<T>::setHeaderRow(uptr<UIBase>&& headerRow) {
		this->headerRow = std::move(headerRow);
		autosize();
		return *this;
	}

	// Updates the menu font used by rows. This will update existing rows to use the new font and will resize the menu
	template <typename T>
	UIMenu<T>& UIMenu<T>::setItemFont(FFont& itemFont) {
		this->itemFont = itemFont;
		for (const uptr<UIEntry<T>>& row : rows) { row.setFont(itemFont); }
		autosize();
		return *this;
	}

	// Updates the label function used for row titles. This will update titles on existing rows and will resize the menu
	template<typename T> UIMenu<T>& UIMenu<T>::setLabelFunc(func<const str(T&)> labelFunc) {
		this->labelFunc = labelFunc;
		for (const uptr<UIEntry<T>>& row : rows) { row->setText(labelFunc(row->item)); }
		autosize();
		return *this;
	}

	// Change the maximum number of rows that can show up at once when viewing the menu
	template <typename T> UIMenu<T>& UIMenu<T>::setMaxRows(int rows) {
		this->maxRows = rows;
		autosize();
		return *this;
	}

	// Unselects all items. DOES invoke the change callback
	template <typename T> void UIMenu<T>::clearSelection() {
		currentIndices.clear();
		if (onChange) { onChange(getSelectedItems()); }
		for (const uptr<UIEntry<T>>& row : rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Manually take down the overlay spawned by this menu
	template <typename T> void UIMenu<T>::forceClosePopup() {
		if (proxy != nullptr) { screenManager::closeOverlay(proxy); }
	}

	// Get all items in the menu regardless of whether they are visible or selected
	template <typename T> vec<T*> UIMenu<T>::getAllItems() {
		return futil::transform<T>(rows, [](const uptr<UIEntry<T>>& row) { return &(row->item); });
	}

	// Returns the entries corresponding with the currently selected indices
	template <typename T> vec<T*> UIMenu<T>::getSelectedItems() {
		vec<T*> items;
		for (int i : currentIndices) { items.push_back(&(rows[i]->item)); }
		return items;
	}

	// Create a proxy overlay for this menu that closes when you click outside of it
	template <typename T> void UIMenu<T>::openPopup() {
		if (proxy == nullptr) {
			screenManager::openOverlay(std::make_unique<UIMenuProxy<T>>(*this));
			proxy = screenManager::getActiveOverlay();
			if (onOpen) {
				onOpen();
			}
		}
	}

	// Forcibly apply the filter function on the rows and update their positions
	template<typename T> void UIMenu<T>::refilterRows()
	{
		syncRowsForRender();
		updateRowPositions();
	}

	// Updates the dimensions of all children too
	template<typename T> void UIMenu<T>::refreshHb() {
		UIBase::refreshHb();
		scrollbar.refreshHb();
		for (const uptr<UIEntry<T>>& row : rows) {
			row->refreshHb();
		}
	}

	// Render all visible rows and the scrollbar if it is shown
	template <typename T> void UIMenu<T>::renderImpl() {
		background.draw(hb.get(), backgroundColor, {0, 0}, 0, sdl::FlipMode::SDL_FLIP_NONE);
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->renderImpl();
		}

		if (headerRow) { headerRow->renderImpl(); }

		scrollbar.render();
	}

	// Update visible rows. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UIMenu<T>::updateImpl() {
		UIBase::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) { rowsForRender[i]->updateImpl(); }

		if (headerRow) { headerRow->updateImpl(); }

		scrollbar.update();

		// TODO handle keyboard/controllers
	}

	// Create a menu row for a new item
	template <typename T> void UIMenu<T>::makeRow(T item) {
		str name = labelFunc(item);
		rows.push_back(uptr<UIEntry<T>>(entryFunc(*this, item, name, rows.size())));
	}

	// Update the selection to include only this row
	template <typename T> void UIMenu<T>::selectSingleRow(UIEntry<T>& entry) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : rows) { row->updateSelectStatus(false); }
		currentIndices.insert(entry.index);
		entry.updateSelectStatus(true);
		if (onChange) { onChange(getSelectedItems()); }
		updateForSelection();
	}

	// If the row exists in the selection, remove it. Otherwise, add it to the selection. Invokes the change callback
	template <typename T> void UIMenu<T>::toggleRow(UIEntry<T>& entry) {
		if (currentIndices.contains(entry.index)) {
			currentIndices.erase(entry.index);
			entry.updateSelectStatus(false);
		}
		else {
			currentIndices.insert(entry.index);
			entry.updateSelectStatus(true);
		}
		if (onChange) { onChange(getSelectedItems()); }
		updateForSelection();
	}

	// Detach the popup proxy and call the close callback
	template<typename T>
	void UIMenu<T>::unsetProxy() {
		proxy = nullptr;
		if (onClose) {
			onClose();
		}
	}

	// Whenever the items contained in the menu change, we need to update the rows that will actually be rendered on the screen with the underlying rows
	// If there's a filter function defined, use it to filter out the available rows to render.
	// Then, make the scrollbar active if the number of rows exceeds the number of rows that can be shown at once
	template <typename T> void UIMenu<T>::syncRowsForRender() {
		if (filterFunc) {
			rowsForRender.clear();
			for (const uptr<UIEntry<T>>& row : rows) {
				UIEntry<T>* entry = row.get();
				if (filterFunc(entry)) {
					rowsForRender.push_back(entry);
				}
			}
		}
		else {
			rowsForRender.resize(rows.size());
			std::transform(rows.begin(), rows.end(), rowsForRender.begin(),
				[](const uptr<UIEntry<T>>& entry) { return entry.get(); });
		}

		scrollbar.enabled = rowsForRender.size() > maxRows;
	}

	// When the items are changed, the rows should be expanded to match the width of the longest projected row if autosizing is enabled. Otherwise, they should match the existing hitbox width minus the scrollbar width
	// The scrollbar should be placed immediately to the right of the items, and it should be expanded vertically to cover all the rows
	// The menu should be expanded to cover the rows as well as the scrollbar
	template <typename T>
	void UIMenu<T>::autosize() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float sizeY = rowCount * (rows.size() > 0 ? rows[0]->hb->h : 0);
		if (canAutosize) {
			float maxWidth = std::transform_reduce(rows.begin(), rows.end(), 0,
			                                       [](float a, float b) { return std::max(a, b); },
			                                       [](const uptr<UIEntry<T>>& row) {
				                                       return row->getProjectedWidth();
			                                       });
			for (const uptr<UIEntry<T>>& row : rows) { row->setHbExactSizeX(maxWidth); }

			scrollbar.hb->setExactPos(hb->x + maxWidth + rMarg, hb->y + rMarg);
			scrollbar.hb->setExactSizeY(sizeY);
			setHbExactSize(maxWidth + scrollbar.hb->w, sizeY + rMarg * 2);
		}
		else {
			float targetWidth = hb->w - scrollbar.hb->w - rMarg;
			for (const uptr<UIEntry<T>>& row : rows) {
				row->setHbExactSizeX(targetWidth);
			}

			scrollbar.hb->setExactPos(hb->x + targetWidth + rMarg, hb->y + rMarg);
			scrollbar.hb->setExactSizeY(sizeY);
			setHbExactSizeY(sizeY + rMarg * 2);
		}

		updateRowPositions();
	}

	// Whenever the scrollbar position changes, we should update the top visible row and row positions
	template <typename T> void UIMenu<T>::onScroll(float percent) {
		int limit = rowsForRender.size() - getVisibleRowCount();
		int newIndex = std::clamp(static_cast<int>(percent * limit), 0, limit);
		if (newIndex != topVisibleRowIndex) {
			topVisibleRowIndex = newIndex;
			updateRowPositions();
		}
	}

	// Hook used to update dropdowns to update their display strings
	template <typename T> void UIMenu<T>::updateForSelection() {
		if (onSelectionUpdate) {
			vec<UIEntry<T>*> items;
			for (int i : currentIndices) { items.push_back(rows[i].get()); }
			onSelectionUpdate(items);
		}
	}

	// Whenever the scrollbar position is changed or items are changed, we need to update the positions of each row
	template <typename T> void UIMenu<T>::updateRowPositions() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float x = hb->x + rMarg;
		float y = (headerRow ? headerRow->hb->y : hb->y) + rMarg;
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->hb->setExactPos(x, y);
			y += rowsForRender[i]->hb->h;
		}
	}

	/*
	 * Statics
	 */

	template<typename T> uptr<UIMenu<T>> UIMenu<T>::multiMenu(Hitbox* hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background) {
		return std::make_unique<UIMenu<T>>(hb,
			[](UIMenu<T>& menu, T& item, str& name, int index) {return multiSelectFunc<T>(menu, item, name, index); },
			labelFunc, itemFont, background);
	}

	template<typename T> uptr<UIMenu<T>> UIMenu<T>::singleMenu(Hitbox* hb,
		func<str(const T&)> labelFunc,
		FFont& itemFont,
		IDrawable& background) {
		return std::make_unique<UIMenu<T>>(hb,
			[](UIMenu<T>& menu, T& item, str& name, int index) {return singleSelectFunc<T>(menu, item, name, index); },
			labelFunc, itemFont, background);
	}

	template <typename T> UIEntry<T>* multiSelectFunc(UIMenu<T>& menu, T& item, str& name, int index) {
		func<void(UIEntry<T>&)> onClick = [&menu](UIEntry<T>& p) { menu.toggleRow(p); };
		UIEntry<T>* entry = new UIEntry<T>(item, index, onClick,
		                           new RelativeHitbox(*menu.hb),
		                           menu.getItemFont(), name);
		entry->setHbExactSizeY(cfg.renderScale(64));
		return entry;
	}

	template <typename T> UIEntry<T>* singleSelectFunc(UIMenu<T>& menu, T& item, str& name, int index) {
		func<void(UIEntry<T>&)> onClick = [&menu](UIEntry<T>& p) { menu.selectSingleRow(p); };
		UIEntry<T>* entry = new UIEntry<T>(item, index, onClick,
		                      new RelativeHitbox(*menu.hb),
		                      menu.getItemFont(), name);
		entry->setHbExactSizeY(cfg.renderScale(64));
		return entry;
	}

	/*
	 * UIMenu Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIMenuProxy<T>::close() { menu.unsetProxy(); }

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIMenuProxy<T>::update() {
		menu.updateImpl();
		if ((sdl::mouseIsLeftJustClicked() && !menu.isHovered()) || sdl::keyboardJustPressedEsc()) { screenManager::closeOverlay(this); }
	}
}
