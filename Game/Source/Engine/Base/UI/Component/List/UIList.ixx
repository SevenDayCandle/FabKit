export module fbc.UIList;

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
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import sdl;
import std;

constexpr int MARGIN = 16;

export namespace fbc {
	export template <typename T> class UIList : public UIBase {
	public:
		UIList(Hitbox* hb,
			func<str(const T&)> labelFunc = futil::toString<T>,
			FFont& itemFont = cct.fontRegular(),
			IDrawable& background = cct.images.panelRound,
			bool canAutosize = false) :
			UIBase(hb), background(background), itemFont(itemFont), labelFunc(labelFunc), canAutosize(canAutosize) {
		}

		~UIList() override {}

		inline void clearItems() { setItems(); }
		inline bool empty() { return rows.empty(); }
		inline FFont& getItemFont() const { return itemFont; }
		inline int size() const { return rows.size(); }

		template <c_itr<T> Iterable> UIList& addItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIList& addItems(const Iterable& items);
		template <c_varg<T>... Args> UIList& addItems(Args&&... items);
		template <c_varg<T*>... Args> UIList& addItems(Args&&... items);
		template <c_itr<T> Iterable> UIList& setItems(const Iterable& items);
		template <c_itr<T*> Iterable> UIList& setItems(const Iterable& items);
		template <c_varg<T>... Args> UIList& setItems(Args&&... items);
		template <c_varg<T*>... Args> UIList& setItems(Args&&... items);
		UIList& setItemFont(FFont& itemFont);
		UIList& setLabelFunc(func<str(const T&)> labelFunc);
		UIList& setMaxRows(int rows);
		vec<const T*> getAllItems();
		void forEach(func<void(const T&)> func);
		void refreshDimensions() override;
		void renderImpl() override;
		void updateImpl() override;

		virtual void selectRow(UIEntry<T>& row) = 0;

	protected:
		bool canAutosize;
		int activeRow = -1;
		int maxRows = 15;
		int topVisibleRowIndex;
		sdl::Color backgroundColor = sdl::COLOR_WHITE;
		IDrawable& background;
		FFont& itemFont = cct.fontRegular();
		func<str(const T&)> labelFunc;
		vec<uptr<UIEntry<T>>> rows;

		inline virtual int getVisibleRowCount() const { return std::min(static_cast<int>(rows.size()), this->maxRows); }
		inline virtual void updateTopVisibleRowIndex(int value) { topVisibleRowIndex = value; }
		inline static float rMargin() { return cfg.renderScale(MARGIN); }

		virtual UIEntry<T>* makeRow(const T& item, int i);
		virtual void refreshRows();
	private:
		virtual void autosize();
		virtual void updateRowPositions();
	};

	/* 
		Function definitions 
	*/

	// Create rows for each item in the provided list
	template <typename T> template <c_itr<T> Iterable> UIList<T>& UIList<T>::addItems(const Iterable& items) {
		for (const T& item : items) {
			rows.push_back(uptr<UIEntry<T>>(makeRow(item, rows.size())));
		}
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (pointer version)
	template <typename T> template <c_itr<T*> Iterable> UIList<T>& UIList<T>::addItems(const Iterable& items) {
		for (T* item : items) {
			rows.push_back(uptr<UIEntry<T>>(makeRow(*item, rows.size())));
		}
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (varargs version)
	template<typename T> template<c_varg<T> ...Args> UIList<T>& UIList<T>::addItems(Args&&... items)
	{
		(rows.push_back(uptr<UIEntry<T>>(makeRow(items, rows.size()))), ...);
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (varargs pointer version)
	template<typename T> template<c_varg<T*> ...Args> UIList<T>& UIList<T>::addItems(Args&&... items)
	{
		(rows.push_back(uptr<UIEntry<T>>(makeRow(*items, rows.size()))), ...);
		refreshRows();
		return *this;
	}

	// Replaces the current rows with rows for each item in the provided list. Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable> UIList<T>& UIList<T>::setItems(const Iterable& items) {
		rows.clear();
		activeRow = -1;
		updateTopVisibleRowIndex(0);
		return addItems(items);
	}

	// Replaces the current rows with rows for each item in the provided list (pointer version). Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <c_itr<T*> Iterable> UIList<T>& UIList<T>::setItems(const Iterable& items) {
		rows.clear();
		activeRow = -1;
		updateTopVisibleRowIndex(0);
		return addItems(items);
	}

	// Replaces the current rows with rows for each item in the provided list (varargs version). Clears any selections in the process, but does NOT invoke the change callback.
	template<typename T> template<c_varg<T> ...Args> UIList<T>& UIList<T>::setItems(Args&&... items) {
		rows.clear();
		activeRow = -1;
		updateTopVisibleRowIndex(0);
		return addItems(items);
	}

	// Replaces the current rows with rows for each item in the provided list (varargs version). Clears any selections in the process, but does NOT invoke the change callback.
	template<typename T> template<c_varg<T*> ...Args> UIList<T>& UIList<T>::setItems(Args&&... items) {
		rows.clear();
		activeRow = -1;
		updateTopVisibleRowIndex(0);
		return addItems(items);
	}

	// Updates the menu font used by rows. This will update existing rows to use the new font and will setExactSize the menu
	template <typename T>
	UIList<T>& UIList<T>::setItemFont(FFont& itemFont) {
		this->itemFont = itemFont;
		for (const uptr<UIEntry<T>>& row : rows) { row.setFont(itemFont); }
		autosize();
		return *this;
	}

	// Updates the label function used for row titles. This will update titles on existing rows and will setExactSize the menu
	template<typename T> UIList<T>& UIList<T>::setLabelFunc(func<str(const T&)> labelFunc) {
		this->labelFunc = labelFunc;
		for (const uptr<UIEntry<T>>& row : rows) { row->setText(labelFunc(row->item)); }
		autosize();
		return *this;
	}

	// Change the maximum number of rows that can show up at once when viewing the menu
	template <typename T> UIList<T>& UIList<T>::setMaxRows(int rows) {
		this->maxRows = rows;
		autosize();
		return *this;
	}

	// Get all items in the menu regardless of whether they are visible or selected
	template <typename T> vec<const T*> UIList<T>::getAllItems() {
		return futil::transform<uptr<UIEntry<T>>, const T*>(rows, [](const uptr<UIEntry<T>>& row) { return &(row->item); });
	}

	// Execute a function on every item in the list
	template<typename T> void UIList<T>::forEach(func<void(const T&)> func)
	{
		for (const uptr<UIEntry<T>>& row : rows) {
			func(row->item);
		}
	}

	// Updates the dimensions of all children too
	template<typename T> void UIList<T>::refreshDimensions() {
		UIBase::refreshDimensions();
		for (const uptr<UIEntry<T>>& row : rows) {
			row->refreshDimensions();
		}
		autosize();
	}

	// Render all visible rows and the scrollbar if it is shown
	template <typename T> void UIList<T>::renderImpl() {
		background.draw(hb.get(), backgroundColor, { 0, 0 }, 0, sdl::FlipMode::SDL_FLIP_NONE);
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rows[i]->renderImpl();
		}
	}

	// Update visible rows. The scrollbar should only be shown if there are enough items to warrant it
	template <typename T> void UIList<T>::updateImpl() {
		UIBase::updateImpl();
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rows[i]->updateImpl();
			if (rows[i]->hb->justHovered()) {
				activeRow = i;
			}
		}

		if (activeRow >= 0) {
			if (cfg.actDirUp.isKeyJustPressed()) {
				activeRow = std::max(0, activeRow - 1);
				if (activeRow < topVisibleRowIndex) {
					updateTopVisibleRowIndex(topVisibleRowIndex - 1);
					updateRowPositions();
				}
			}
			else if (cfg.actDirDown.isKeyJustPressed()) {
				activeRow = std::min((int) rows.size() - 1, activeRow + 1);
				if (activeRow > topVisibleRowIndex + maxRows) {
					updateTopVisibleRowIndex(topVisibleRowIndex + 1);
					updateRowPositions();
				}
			}
			else if (sdl::mouseIsLeftJustClicked() && !isHovered()) {
				activeRow = -1;
			}
		}

		for (int i = 0; i < rows.size(); ++i) {
			rows[i]->updateActiveStatus(this->activeRow == i);
		}

		if (this->activeRow >= 0 && cfg.actSelect.isKeyJustPressed()) {
			this->selectRow(*rows[this->activeRow]);
		}
	}

	// Create a menu row for a new item
	template <typename T> UIEntry<T>* UIList<T>::makeRow(const T& item, int i) {
		UIEntry<T>* entry = new UIEntry<T>(item,
			i,
			[this](UIEntry<T>& p) { this->selectRow(p); },
			new RelativeHitbox(*this->hb),
			this->getItemFont(),
			labelFunc(item));
		entry->setHbExactSizeY(cfg.renderScale(64));
		return entry;
	}


	// When the items are changed, the rows should be expanded to match the width of the longest projected row if autosizing is enabled. Otherwise, they should match the existing hitbox width minus the scrollbar width
	// The scrollbar should be placed immediately to the right of the items, and it should be expanded vertically to cover all the rows
	// The menu should be expanded to cover the rows as well as the scrollbar
	template <typename T>
	void UIList<T>::autosize() {
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

			setHbExactSize(maxWidth, sizeY + rMarg * 2);
		}
		else {
			float targetWidth = hb->w - rMarg;
			for (const uptr<UIEntry<T>>& row : rows) {
				row->setHbExactSizeX(targetWidth);
			}

			setHbExactSizeY(sizeY + rMarg * 2);
		}

		updateRowPositions();
	}

	// Triggers whenever the available rows are changed
	template<typename T> void UIList<T>::refreshRows() {
		autosize();
	}

	// Whenever the scrollbar position is changed or items are changed, we need to update the positions of each row
	template <typename T> void UIList<T>::updateRowPositions() {
		int rowCount = getVisibleRowCount();
		float rMarg = rMargin();
		float x = hb->x + rMarg;
		float y = hb->y + rMarg;
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rows[i]->hb->setExactPos(x, y);
			y += rows[i]->hb->h;
		}
	}
}