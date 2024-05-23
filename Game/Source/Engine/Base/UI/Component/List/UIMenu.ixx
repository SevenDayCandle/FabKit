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
import fbc.UIList;
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import sdl;
import std;

constexpr int MARGIN = 16;

export namespace fbc {
	export template <typename T> class UIMenu : public UIList<T> {

	public:
		UIMenu(Hitbox* hb,
		       func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
		       FFont& itemFont = cct.fontRegular(),
		       IDrawable& background = cct.images.hoverPanel):
			UIList<T>(hb, labelFunc, itemFont, background),
			scrollbar(new RelativeHitbox(*hb, 0, 0, 48, 48)) { scrollbar.setOnScroll([this](float f) { onScroll(f); }); }

		~UIMenu() override {}

		inline bool isOpen() const { return proxy != nullptr; }
		inline UIMenu& setFilterFunc(func<bool(UIEntry<T>*)> filterFunc) { return this->filterFunc = filterFunc, *this; }
		inline UIMenu& setItemFont(FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UIMenu& setLabelFunc(func<const str(T&)> labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UIMenu& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), *this; }
		inline UIMenu& setOnChange(func<void(vec<T*>)> onChange) { return this->onChange = onChange, *this; }
		inline UIMenu& setOnClose(func<void()> onClose) { return this->onClose = onClose, *this; }
		inline UIMenu& setOnOpen(func<void()> onOpen) { return this->onOpen = onOpen, *this; }
		inline UIMenu& setOnSelectionUpdate(func<void(vec<UIEntry<T>*>&)> onSelectionUpdate) {return this->onSelectionUpdate = onSelectionUpdate, *this;}

		inline int selectedSize() const { return currentIndices.size(); }

		UIMenu& setSelectionLimit(int rows);
		vec<T*> getSelectedItems();
		void clearSelection();
		void forceClosePopup();
		void openPopup();
		void refilterRows();
		void refreshHb() override;
		void renderImpl() override;
		template <c_itr<int> Iterable> void selectIndices(Iterable& indices);
		template <c_itr<T&> Iterable> void selectSelection(Iterable& items);
		void selectRow(UIEntry<T>& entry) override;
		void unsetProxy();
		void updateImpl() override;
		template <c_itr<int> Iterable> void updateIndices(Iterable& indices);
		template <c_itr<T> Iterable> void updateSelection(Iterable& indices);

		static uptr<UIMenu> multiMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.hoverPanel);
		static uptr<UIMenu> singleMenu(Hitbox* hb, func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); }, FFont& itemFont = cct.fontRegular(), IDrawable& background = cct.images.hoverPanel);
	protected:
		set<int> currentIndices;
		vec<UIEntry<T>*> rowsForRender;

		inline int getVisibleRowCount() const { return std::min(static_cast<int>(rowsForRender.size()), this->maxRows); }

	private:
		int selectionLimit = std::numeric_limits<int>::max();
		func<bool(UIEntry<T>*)> filterFunc;
		func<void(vec<T*>)> onChange;
		func<void()> onClose;
		func<void()> onOpen;
		func<void(vec<UIEntry<T>*>&)> onSelectionUpdate;
		UIVerticalScrollbar scrollbar;
		IOverlay* proxy;

		inline static float rMargin() { return cfg.renderScale(MARGIN); }

		void autosize();
		void changeEvent();
		void onScroll(float percent);
		void rowsChangedEvent();
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

	// Updates the selected indexes. DOES invoke the change callback.
	template <typename T> template <c_itr<int> Iterable> void UIMenu<T>::selectIndices(Iterable& indices) {
		updateIndices(indices);
		changeEvent();
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template <typename T> template <c_itr<T&> Iterable> void UIMenu<T>::selectSelection(Iterable& items) {
		updateSelection(items);
		changeEvent();
	}

	// Updates the selected indexes. Does NOT invoke the change callback.
	template <typename T> template <c_itr<int> Iterable> void UIMenu<T>::updateIndices(Iterable& indices) {
		currentIndices.clear();
		currentIndices.insert(indices.begin(), indices.end());
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable> void UIMenu<T>::updateSelection(Iterable& items) {
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			opt<T> res = futil::find(items, row->item);
			if (res != std::nullopt) { currentIndices.insert(row.index); }
		}
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Change the maximum number of rows that can be selected. If there were previously more selected rows than this limit, prunes off rows to meet the selection limit
	template<typename T> UIMenu<T>& UIMenu<T>::setSelectionLimit(int rows)
	{
		this->selectionLimit = std::clamp(rows, 0, std::numeric_limits<int>::max());
		return *this;
	}

	// Unselects all items. DOES invoke the change callback
	template <typename T> void UIMenu<T>::clearSelection() {
		currentIndices.clear();
		changeEvent();
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(currentIndices.contains(row->index)); }
		updateForSelection();
	}

	// Manually take down the overlay spawned by this menu
	template <typename T> void UIMenu<T>::forceClosePopup() {
		if (proxy != nullptr) { screenManager::closeOverlay(proxy); }
	}

	// Returns the entries corresponding with the currently selected indices
	template <typename T> vec<T*> UIMenu<T>::getSelectedItems() {
		vec<T*> items;
		for (int i : currentIndices) { items.push_back(&(this->rows[i]->item)); }
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
		UIList<T>::refreshHb();
		scrollbar.refreshHb();
	}

	// Render all visible rows and the scrollbar if it is shown
	template <typename T> void UIMenu<T>::renderImpl() {
		this->background.draw(this->hb.get(), this->backgroundColor, {0, 0}, 0, sdl::FlipMode::SDL_FLIP_NONE);
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) {
			rowsForRender[i]->renderImpl();
		}

		scrollbar.render();
	}

	// Update visible rows. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UIMenu<T>::updateImpl() {
		UIBase::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = this->topVisibleRowIndex; i < this->topVisibleRowIndex + rowCount; ++i) { rowsForRender[i]->updateImpl(); }

		scrollbar.update();

		// TODO handle keyboard/controllers
	}

	// If the row exists in the selection, remove it. Otherwise, add it to the selection. Invokes the change callback
	template <typename T> void UIMenu<T>::selectRow(UIEntry<T>& entry) {
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
	void UIMenu<T>::autosize() {
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
			scrollbar.hb->setExactSizeY(sizeY);
			this->setHbExactSize(maxWidth + scrollbar.hb->w, sizeY + rMarg * 2);
		}
		else {
			float targetWidth = this->hb->w - scrollbar.hb->w - rMarg;
			for (const uptr<UIEntry<T>>& row : this->rows) {
				row->setHbExactSizeX(targetWidth);
			}

			scrollbar.hb->setExactPos(this->hb->x + targetWidth + rMarg, this->hb->y + rMarg);
			scrollbar.hb->setExactSizeY(sizeY);
			this->setHbExactSizeY(sizeY + rMarg * 2);
		}

		updateRowPositions();
	}

	template<typename T> void UIMenu<T>::changeEvent() {
		if (onChange) {
			onChange(getSelectedItems());
		}
	}

	// Whenever the scrollbar position changes, we should update the top visible row and row positions
	template <typename T> void UIMenu<T>::onScroll(float percent) {
		int limit = rowsForRender.size() - getVisibleRowCount();
		int newIndex = std::clamp(static_cast<int>(percent * limit), 0, limit);
		if (newIndex != this->topVisibleRowIndex) {
			this->topVisibleRowIndex = newIndex;
			updateRowPositions();
		}
	}

	// When the rows are changed, reposition the rows and sort them, and clear out your current selection because it will likely no longer be valid
	template<typename T> void UIMenu<T>::rowsChangedEvent() {
		currentIndices.clear();
		syncRowsForRender();
		autosize();
		updateForSelection();
	}

	// Hook used to update dropdowns to update their display strings
	template <typename T> void UIMenu<T>::updateForSelection() {
		if (onSelectionUpdate) {
			vec<UIEntry<T>*> items;
			for (int i : currentIndices) { items.push_back(this->rows[i].get()); }
			onSelectionUpdate(items);
		}
	}

	// Whenever the scrollbar position is changed or items are changed, we need to update the positions of each row
	template <typename T> void UIMenu<T>::updateRowPositions() {
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

	template<typename T> uptr<UIMenu<T>> UIMenu<T>::multiMenu(Hitbox* hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background) {
		return std::make_unique<UIMenu<T>>(hb, labelFunc, itemFont, background);
	}

	template<typename T> uptr<UIMenu<T>> UIMenu<T>::singleMenu(Hitbox* hb,
		func<str(const T&)> labelFunc,
		FFont& itemFont,
		IDrawable& background) {
		uptr<UIMenu<T>> res = std::make_unique<UIMenu<T>>(hb, labelFunc, itemFont, background);
		res->setSelectionLimit(1);
		return res;
	}
	/*
	 * UIMenuProxy Implementations
	 */

	// When closed, unlink this from its menu
	template <typename T> void UIMenuProxy<T>::close() { menu.unsetProxy(); }

	// Close the menu if the user clicks outside the menu
	template <typename T> void UIMenuProxy<T>::update() {
		menu.updateImpl();
		if ((sdl::mouseIsLeftJustClicked() && !menu.isHovered()) || sdl::keyboardJustPressedEsc()) { screenManager::closeOverlay(this); }
	}
}
