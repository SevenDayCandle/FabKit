export module fab.UIList;

import fab.FFont;
import fab.Hitbox;
import fab.IDrawable;
import fab.FWindow;
import fab.RelativeHitbox;
import fab.UIBase;
import fab.UIEntry;
import fab.UIVerticalScrollbar;
import fab.FUtil;
import fab.FWindow;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	constexpr int MARGIN = 16;

	export template <typename T> class UIList : public UIBase {
	public:
		class ConstIterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = const UIEntry<T>;
			using difference_type = std::ptrdiff_t;
			using pointer = const UIEntry<T>*;
			using reference = const UIEntry<T>&;

			ConstIterator(typename vec<uptr<UIEntry<T>>>::const_iterator it) : it(it) {}

			reference operator*() const { return *(*it); }
			pointer operator->() const { return (*it).get(); }

			ConstIterator& operator++() { return ++it, * this; }
			ConstIterator operator++(int) {
				ConstIterator tmp = *this;
				++it;
				return tmp;
			}

			friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.it == b.it; }
			friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.it != b.it; }

		private:
			typename vec<uptr<UIEntry<T>>>::const_iterator it;
		};

		class Iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = UIEntry<T>;
			using difference_type = std::ptrdiff_t;
			using pointer = UIEntry<T>*;
			using reference = UIEntry<T>&;

			Iterator(typename vec<uptr<UIEntry<T>>>::iterator it) : it(it) {}

			reference operator*() const { return *(*it); }
			pointer operator->() const { return (*it).get(); }

			Iterator& operator++() {return ++it, *this;}
			Iterator operator++(int) {
				Iterator tmp = *this;
				++it;
				return tmp;
			}

			friend bool operator==(const Iterator& a, const Iterator& b) { return a.it == b.it; }
			friend bool operator!=(const Iterator& a, const Iterator& b) { return a.it != b.it; }

		private:
			typename vec<uptr<UIEntry<T>>>::iterator it;
		};

		UIList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize = false) :
			UIBase(window, move(hb)), background(background), itemFont(itemFont), labelFunc(move(labelFunc)), canAutosize(canAutosize) {}
		UIList(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc = futil::toString<T>, bool canAutosize = false) :
			UIList(window, move(hb), move(labelFunc), window.props.fontSmall(), window.props.defaultBackground(), canAutosize) {}
		UIList(UIList&& other) noexcept = default;

		~UIList() override {}

		inline bool empty() { return rows.empty(); }
		inline ConstIterator begin() const { return ConstIterator(rows.cbegin()); }
		inline ConstIterator end() const { return ConstIterator(rows.cend()); }
		inline FFont& getItemFont() const { return itemFont; }
		inline Iterator begin() { return Iterator(rows.begin()); }
		inline Iterator end() { return Iterator(rows.end()); }
		inline size_t size() const { return rows.size(); }
		inline vec<const T*> toVec() const { return futil::transform(rows, [](uptr<UIEntry<T>>& row) { return &(row->item); }); }
		inline void clearItems() { setItems(); }

		template <c_itr<T> Iterable> UIList& addItems(Iterable& items);
		template <c_itr<T*> Iterable> UIList& addItems(Iterable& items);
		template <c_varg<T>... Args> UIList& addItems(Args&&... items);
		template <c_varg<T*>... Args> UIList& addItems(Args&&... items);
		template <c_itr<T> Iterable> UIList& setItems(Iterable& items);
		template <c_itr<T*> Iterable> UIList& setItems(Iterable& items);
		template <c_varg<T>... Args> UIList& setItems(Args&&... items);
		template <c_varg<T*>... Args> UIList& setItems(Args&&... items);
		UIList& setItemFont(const FFont& itemFont);
		UIList& setLabelFunc(const func<str(const T&)>& labelFunc);
		UIList& setLabelFunc(func<str(const T&)>&& labelFunc);
		UIList& setMaxRows(int rows);
		void refreshDimensions() override;
		void renderImpl(BatchRenderPass& rp) override;
		void updateImpl() override;

		virtual void selectRow(UIEntry<T>& row) = 0;

	protected:
		bool canAutosize;
		int activeRow = -1;
		int maxRows = 15;
		int topVisibleRowIndex;
		sdl::Color backgroundColor = sdl::COLOR_STANDARD;
		IDrawable& background;
		FFont& itemFont;
		func<str(const T&)> labelFunc;
		vec<uptr<UIEntry<T>>> rows;

		inline virtual float rMargin() { return win.renderScale(MARGIN); }
		inline virtual int getVisibleRowCount() const { return std::min(static_cast<int>(rows.size()), this->maxRows); }
		inline virtual void updateTopVisibleRowIndex(int value) { topVisibleRowIndex = value; }

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
	template <typename T> template <c_itr<T> Iterable> UIList<T>& UIList<T>::addItems(Iterable& items) {
		for (const T& item : items) {
			rows.push_back(uptr<UIEntry<T>>(makeRow(item, static_cast<int>(rows.size()))));
		}
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (pointer version)
	template <typename T> template <c_itr<T*> Iterable> UIList<T>& UIList<T>::addItems(Iterable& items) {
		for (T* item : items) {
			rows.push_back(uptr<UIEntry<T>>(makeRow(*item, static_cast<int>(rows.size()))));
		}
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (varargs version)
	template<typename T> template<c_varg<T> ...Args> UIList<T>& UIList<T>::addItems(Args&&... items)
	{
		(rows.push_back(uptr<UIEntry<T>>(makeRow(items, static_cast<int>(rows.size())))), ...);
		refreshRows();
		return *this;
	}

	// Create rows for each item in the provided list (varargs pointer version)
	template<typename T> template<c_varg<T*> ...Args> UIList<T>& UIList<T>::addItems(Args&&... items)
	{
		(rows.push_back(uptr<UIEntry<T>>(makeRow(*items, static_cast<int>(rows.size())))), ...);
		refreshRows();
		return *this;
	}

	// Replaces the current rows with rows for each item in the provided list. Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <c_itr<T> Iterable> UIList<T>& UIList<T>::setItems(Iterable& items) {
		rows.clear();
		activeRow = -1;
		updateTopVisibleRowIndex(0);
		return addItems(items);
	}

	// Replaces the current rows with rows for each item in the provided list (pointer version). Clears any selections in the process, but does NOT invoke the change callback.
	template <typename T> template <c_itr<T*> Iterable> UIList<T>& UIList<T>::setItems(Iterable& items) {
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

	// Updates the menu font used by rows. This will update existing rows to use the new font and will setRealSize the menu
	template <typename T>
	UIList<T>& UIList<T>::setItemFont(const FFont& itemFont) {
		this->itemFont = itemFont;
		for (const uptr<UIEntry<T>>& row : rows) { row.setFont(itemFont); }
		autosize();
		return *this;
	}

	// Updates the label function used for row titles. This will update titles on existing rows and will setRealSize the menu
	template<typename T> UIList<T>& UIList<T>::setLabelFunc(const func<str(const T&)>& labelFunc) {
		this->labelFunc = labelFunc;
		for (const uptr<UIEntry<T>>& row : rows) { row->setText(this->labelFunc(row->item)); }
		autosize();
		return *this;
	}

	template<typename T> UIList<T>& UIList<T>::setLabelFunc(func<str(const T&)>&& labelFunc) {
		this->labelFunc = move(labelFunc);
		for (const uptr<UIEntry<T>>& row : rows) { row->setText(this->labelFunc(row->item)); }
		autosize();
		return *this;
	}

	// Change the maximum number of rows that can show up at once when viewing the menu
	template <typename T> UIList<T>& UIList<T>::setMaxRows(int rows) {
		this->maxRows = rows;
		autosize();
		return *this;
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
	template <typename T> void UIList<T>::renderImpl(BatchRenderPass& rp) {
		background.draw(rp, *hb.get(), 1, 1, 0, &backgroundColor);
		int rowCount = getVisibleRowCount();
		for (int i = topVisibleRowIndex; i < topVisibleRowIndex + rowCount; ++i) {
			rows[i]->renderImpl(rp);
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
			if (win.props.hasPressedDirUp()) {
				activeRow = std::max(0, activeRow - 1);
				if (activeRow < topVisibleRowIndex) {
					updateTopVisibleRowIndex(topVisibleRowIndex - 1);
					updateRowPositions();
				}
			}
			else if (win.props.hasPressedDirDown()) {
				activeRow = std::min(static_cast<int>(rows.size()) - 1, activeRow + 1);
				if (activeRow > topVisibleRowIndex + maxRows) {
					updateTopVisibleRowIndex(topVisibleRowIndex + 1);
					updateRowPositions();
				}
			}
			else if (sdl::runner::mouseIsLeftJustClicked() && !isHovered()) {
				activeRow = -1;
			}
		}

		for (int i = 0; i < rows.size(); ++i) {
			rows[i]->updateActiveStatus(this->activeRow == i);
		}

		if (this->activeRow >= 0 && win.props.hasPressedSelect()) {
			this->selectRow(*rows[this->activeRow]);
		}
	}

	// Create a menu row for a new item
	template <typename T> UIEntry<T>* UIList<T>::makeRow(const T& item, int i) {
		UIEntry<T>* entry = new UIEntry<T>(item,
			i,
			[this](UIEntry<T>& p) { this->selectRow(p); },
			this->win,
			this->relhb(),
			this->getItemFont(),
			labelFunc(item));
		entry->setHbExactSizeY(win.renderScale(64));
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
			rows[i]->hb->setRealPos(x, y);
			y += rows[i]->hb->h;
		}
	}
}