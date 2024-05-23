export module fbc.UINavigation;

import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIEntry;
import fbc.UIList;
import sdl;
import std;

export namespace fbc {
	export template <typename T> class UINavigation : public UIList<T> {
	public:
		UINavigation(Hitbox* hb): UIList<T>() {}
		virtual ~UINavigation() {}

		inline T* getSelectedItem() { return this->rows[currentIndex]; }
		inline UINavigation& setItemFont(FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UINavigation& setLabelFunc(func<const str(T&)> labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UINavigation& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), * this; }
		inline UINavigation& setOnChange(func<void(T*)> onChange) { return this->onChange = onChange, *this; }

		void select(int ind);
		void select(T& item);
		void selectRow(UIEntry<T>& entry) override;
	protected:
		int currentIndex;
	private:
		func<void(T*)> onChange;

		void changeEvent();
	};

	template<typename T> void UINavigation<T>::select(int ind)
	{
		currentIndex = ind;
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(row->index == ind); }
	}

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