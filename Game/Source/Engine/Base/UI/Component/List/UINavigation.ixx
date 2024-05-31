export module fbc.UINavigation;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIEntry;
import fbc.UIList;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UINavigation : public UIList<T> {
	public:
		UINavigation(Hitbox* hb,
			func<str(const T&)> labelFunc = [](const T& item) { return futil::toString(item); },
			FFont& itemFont = cct.fontRegular(),
			IDrawable& background = cct.images.hoverPanel) :
			UIList<T>(hb, labelFunc, itemFont, background) {}
		virtual ~UINavigation() {}

		inline const T* getSelectedItem() { return &this->rows[currentIndex]->item; }
		inline UINavigation& setItemFont(FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UINavigation& setLabelFunc(func<const str(T&)> labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UINavigation& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), * this; }
		inline UINavigation& setOnChange(func<void(const T*)> onChange) { return this->onChange = onChange, *this; }

		void select(int ind);
		void select(T& item);
		void selectRow(UIEntry<T>& entry) override;
	protected:
		int currentIndex = 0;
	private:
		func<void(const T*)> onChange;

		void changeEvent();
	};

	// Selects the row matching the given index
	template<typename T> void UINavigation<T>::select(int ind)
	{
		currentIndex = ind;
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(row->index == ind); }
	}

	// Selects the row matching the given item
	template<typename T> void UINavigation<T>::select(T& item)
	{
		for (const uptr<UIEntry<T>>& row : this->rows) { 
			if (row->item == item) {
				currentIndex = row->index;
				row->updateSelectStatus(true);
			}
			else {
				row->updateSelectStatus(false);
			}
		}
	}

	// Directly select a row entry
	template<typename T> void UINavigation<T>::selectRow(UIEntry<T>& entry)
	{
		currentIndex = entry.index;
		entry.updateSelectStatus(true);
		changeEvent();
	}

	template<typename T> void UINavigation<T>::changeEvent()
	{
		if (onChange) {
			onChange(getSelectedItem());
		}
	}
}