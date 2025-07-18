export module fab.UINavigation;

import fab.EmptyDrawable;
import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.RelativeHitbox;
import fab.UIEntry;
import fab.UIBase;
import fab.UIList;
import sdl.SDLBase; 
import fab.BatchRenderPass; 
import sdl.SDLRunner;
import std;

namespace fab {
	export template <c_ext<UIBase> T> class UINavigation : public UIList<T> {
	public:
		UINavigation(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize) :
			UIList<T>(window, move(hb), std::move(labelFunc), itemFont, background, canAutosize) {}
		UINavigation(FWindow& window, uptr<Hitbox>&& hb) :
			UINavigation(window, std::move(hb), futil::toString<T>, window.props.fontRegular(), window.props.defaultBackground(), false) {}

		inline T* getSelectedItem() { return currentItem; }
		inline UINavigation& setItemFont(FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UINavigation& setLabelFunc(const func<const str(T&)>& labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UINavigation& setLabelFunc(func<const str(T&)>&& labelFunc) { return UIList<T>::setLabelFunc(move(labelFunc)), * this; }
		inline UINavigation& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), * this; }

		virtual bool isHovered() override;
		void refreshDimensions() override;
		void renderImpl(BatchRenderPass& rp) override;
		void select(int ind);
		void select(T& item);
		void selectRow(UIEntry<T>& entry) override;
		void updateImpl() override;
	protected:
		T* currentItem;

		virtual UIEntry<T>* makeRow(const T& item, int i) override;
	private:
		void refreshRows() override;
	};

	template<c_ext<UIBase> T> bool UINavigation<T>::isHovered()
	{
		return UIList<T>::isHovered() || (currentItem && currentItem->isHovered());
	}

	template<c_ext<UIBase> T> void UINavigation<T>::refreshDimensions()
	{
		UIList<T>::refreshDimensions();
		for (const uptr<UIEntry<T>>& row : this->rows) {
			const_cast<T&>(row->item).refreshDimensions();
		}
	}

	// Render the currently selected page
	template<c_ext<UIBase> T> void UINavigation<T>::renderImpl(BatchRenderPass& rp)
	{
		UIList<T>::renderImpl(rp);
		if (currentItem) {
			currentItem->renderImpl(rp);
		}
	}

	// Selects the row matching the given index
	template<c_ext<UIBase> T> void UINavigation<T>::select(int ind)
	{
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (row->index == ind) {
				currentItem = const_cast<T*>(&row->item);
				row->updateSelectStatus(true);
			}
			else {
				row->updateSelectStatus(false);
			}
		}
	}

	// Selects the row matching the given item
	template<c_ext<UIBase> T> void UINavigation<T>::select(T& item)
	{
		for (const uptr<UIEntry<T>>& row : this->rows) {
			if (row->item == item) {
				currentItem = const_cast<T*>(&row->item);
				row->updateSelectStatus(true);
			}
			else {
				row->updateSelectStatus(false);
			}
		}
	}

	// Directly select a row entry
	template<c_ext<UIBase> T> void UINavigation<T>::selectRow(UIEntry<T>& entry)
	{
		currentItem = const_cast<T*>(&entry.item);
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(row->index == entry.index); }
	}

	// Update the currently selected page
	template<c_ext<UIBase> T> void UINavigation<T>::updateImpl()
	{
		UIList<T>::updateImpl();
		if (currentItem) {
			currentItem->updateImpl();
		}
	}

	template<c_ext<UIBase> T> UIEntry<T>* UINavigation<T>::makeRow(const T& item, int i)
	{
		UIEntry<T>* entry = new UIEntry<T>(item,
			i,
			[this](UIEntry<T>& p) { this->selectRow(p); },
			this->win,
			this->relhb(),
			this->getItemFont(),
			this->labelFunc(item),
			EMPTY,
			this->win.props.defaultArrow());
		entry->setHbExactSizeY(this->win.renderScale(64));
		return entry;
	}

	// Ensure that an item is always selected if the list has items. Conversely, if the list is empty, ensure that nothing is selected
	template<c_ext<UIBase> T> void UINavigation<T>::refreshRows()
	{
		UIList<T>::refreshRows();
		if ((currentItem == nullptr && !this->empty()) || !std::ranges::any_of(this->rows, [this](const uptr<UIEntry<T>>& row) {return &row->item == currentItem; })) {
			select(0);
		}
		else if (this->empty()) {
			currentItem = nullptr;
		}
	}
}