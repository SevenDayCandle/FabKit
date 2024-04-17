export module fbc.uiMenu;

import fbc.coreContent;
import fbc.ffont;
import fbc.hitbox;
import fbc.relativeHitbox;
import fbc.screenManager;
import fbc.uiBase;
import fbc.uiEntry;
import fbc.uiHoverable;
import fbc.uiVerticalScrollbar;
import fbc.futil;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UIMenu : public UIHoverable {
		class UIMenuProxy : public UIBase {
			UIMenuProxy(UIMenu<T>& menu): menu(menu) {}

			UIMenu<T>& menu;

			inline void renderImpl() override { menu.renderImpl(); };

			void close() override;
			void updateImpl() override;
		};

	public:
		UIMenu(Hitbox* hb,
			func<uptr<UIEntry<T>(T, Hitbox&, str&, FFont&, int)>> entryFunc = singleSelectFunc, 
			func<str(T)> labelFunc = futil::toString,
			FFont& itemFont = cct.fontRegular()):
		UIHoverable(hb), entryFunc(entryFunc), labelFunc(labelFunc), itemFont(itemFont), scrollbar(new RelativeHitbox(*hb)) {}
		~UIMenu() override {}

		inline void clearItems() { setItems(); }
		inline bool isOpen() { return proxy != nullptr; }
		inline int size() { return rows.size(); }

		static uptr<UIEntry<T>> multiSelectFunc(T item, Hitbox& hb, str& name, FFont& itemFont, int index);
		static uptr<UIEntry<T>> singleSelectFunc(T item, Hitbox& hb, str& name, FFont& itemFont, int index);

		template <IterOf<T> Iterable> UIMenu& addItems(Iterable& items);
		template <IterOf<T> Iterable> UIMenu& setItems(Iterable& items);
		UIMenu& setItemFont(FFont& itemFont);
		UIMenu& setMaxRows(int rows);
		vec<T&> getAllItems();
		vec<T&> getSelectedItems();
		void clearSelection();
		void forceClosePopup();
		void openPopup();
		void renderImpl() override;
		template <IterOf<T> Iterable> void select(Iterable& items);
		template <IterOf<int> Iterable> void selectIndices(Iterable& indices);
		void updateImpl() override;
		template <IterOf<int> Iterable> void updateIndices(Iterable& indices);
		template <IterOf<T> Iterable> void updateSelection(Iterable& indices);
	protected:
		FFont& itemFont = cct.fontRegular();
		func<uptr<UIEntry<T>(T, Hitbox&, str&, FFont&, int)>> entryFunc;
		func<str(T)> labelFunc;
		set<int> currentIndices;
		vec<uptr<UIEntry<T>>> rows;
		vec<UIEntry<T>*> rowsForRender;

		inline int getVisibleRowCount() { return std::min(rowsForRender.size(), maxRows); }

		void makeRow(T item);
		virtual void syncRowsForRender();
		virtual void updateForSelection();
	private:
		bool canAutosize;
		int maxRows = 15;
		int topVisibleRowIndex;
		func<void(vec<T&>)> onChange;
		func<void(vec<T&>)> onClose;
		func<void(vec<T&>)> onOpen;
		uptr<UIHoverable> headerRow;
		UIVerticalScrollbar scrollbar;
		UIBase* proxy;

		inline bool shouldShowSlider() { return rowsForRender.size() > maxRows; }

		void autosize();
	};

	// Create rows for each item in the provided list
	template <typename T> template <IterOf<T> Iterable>
	UIMenu<T>& UIMenu<T>::addItems(Iterable& items) {
		for (const T item : items) { makeRow(item); }
		syncRowsForRender();
		autosize();
		return *this;
	}

	// Replaces the current rows with rows for each item in the provided list. Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <IterOf<T> Iterable>
	UIMenu<T>& UIMenu<T>::setItems(Iterable& items) {
		currentIndices.clear();
		rows.clear();
		topVisibleRowIndex = 0;
		return addItems(items);
	}

	// Updates the selected indexes based on the given items. DOES invoke the change callback.
	template<typename T> template<IterOf<T> Iterable>
	void UIMenu<T>::select(Iterable& items)
	{
		updateSelection(items);
		if (onChange) {
			onChange(getSelectedItems());
		}
	}

	// Updates the selected indexes. DOES invoke the change callback.
	template<typename T> template<IterOf<int> Iterable>
	void UIMenu<T>::selectIndices(Iterable& indices)
	{
		updateIndices(indices);
		if (onChange) {
			onChange(getSelectedItems());
		}
	}

	// Updates the selected indexes. Does NOT invoke the change callback.
	template<typename T> template<IterOf<int> Iterable>
	void UIMenu<T>::updateIndices(Iterable& indices)
	{
		currentIndices.clear();
		currentIndices.insert(indices.begin(), indices.end());
		updateForSelection();
	}

	// Updates the selected indexes based on the given items. Does NOT invoke the change callback.
	template<typename T> template<IterOf<T> Iterable>
	void UIMenu<T>::updateSelection(Iterable& items)
	{
		currentIndices.clear();
		for (const uptr<UIEntry<T>>& row : rows) {
			opt<T> res = futil::find(items, row->item);
			if (res != std::nullopt) {
				currentIndices.insert(row.index);
			}
		}
		updateForSelection();
	}

	// Updates the menu font used by rows. This will update existing rows to use the new font, and will resize the menu as necessary
	template<typename T>
	UIMenu<T>& UIMenu<T>::setItemFont(FFont& itemFont)
	{
		this->itemFont = itemFont;
		for (const uptr<UIEntry<T>>& row : rows) {
			row.setFont(itemFont);
		}
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
		if (onChange) {
			onChange(getSelectedItems());
		}
	}

	// Get all items in the menu regardless of whether they are visible or selected
	template <typename T> vec<T&> UIMenu<T>::getAllItems() {
		return futil::map(rows, [](const uptr<UIEntry<T>>& row) { return row->item; });
	}

	// Returns the entries corresponding with the currently selected indices
	template <typename T> vec<T&> UIMenu<T>::getSelectedItems() {
		vec<T&> items;
		for (int i : currentIndices) { items.push_back(rows[i]->item); }
		return items;
	}

	// Create a proxy overlay for this menu that closes when you click outside of it
	template<typename T> void UIMenu<T>::openPopup() {
		if (proxy == nullptr) {
			screenManager::openOverlay(std::make_unique<UIMenuProxy>(this));
			proxy = screenManager::getActiveOverlay();
		}
	}

	// Update the rows that are currently visible. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UIMenu<T>::updateImpl() {
		UIHoverable::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) { rowsForRender[i]->updateImpl(); }

		if (headerRow) { headerRow->updateImpl(); }

		if (shouldShowSlider()) { scrollbar.updateImpl(); }

		// TODO handle keyboard/controllers
	}

	// Create a menu row for a new item
	template <typename T> void UIMenu<T>::makeRow(T item) {
		str name = labelFunc(item);
		rows.push_back(entryFunc(item, *hb, name, rows.size()));
	}

	// Whenever the items contained in the menu change, we need to update the rows that will actually be rendered on the screen with the underlying rows
	// Derivative classes may modify this logic to restrain the rows to be rendered to a certain subset
	template <typename T> void UIMenu<T>::syncRowsForRender() {
		std::transform(rows.begin(), rows.end(), rowsForRender.begin(),
		               [](const uptr<UIEntry<T>>& entry) { return entry.get(); });
	}

	/*
	 * Statics
	 */

	template <typename T> uptr<UIEntry<T>> UIMenu<T>::singleSelectFunc(T item, Hitbox& hb, str& name, FFont& itemFont, int index) {
		auto rh = RelativeHitbox(hb, hb.getOffsetWidth(), hb.getOffsetHeight());
		return uptr<UIEntry<T>>(item, index, hb, itemFont, name);
	}

	/*
	 * UIMenu Implementations
	 */

	// Close the menu if the user clicks outside the menu
	template <typename T>
	void UIMenu<T>::UIMenuProxy::updateImpl() {
		menu.updateImpl();
		if (sdl::mouseIsLeftJustClicked() && !menu.isHovered()) {
			screenManager::closeOverlay(this);
		}
	}
}
