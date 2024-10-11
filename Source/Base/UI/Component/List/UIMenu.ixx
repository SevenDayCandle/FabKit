export module fbc.UIMenu;

import fbc.EmptyDrawable;
import fbc.FFont;
import fbc.FWindow;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.RelativeHitbox;
import fbc.UIEntry;
import fbc.UIList;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export template <typename T> class UIMenu : public UIList<T> {
	public:
		UIMenu(FWindow& window, uptr<Hitbox>&& hb, func<str(const T&)> labelFunc, FFont& itemFont, IDrawable& background, bool canAutosize) :
			UIList<T>(window, move(hb), std::move(labelFunc), itemFont, background, canAutosize) {}
		UIMenu(FWindow& window, uptr<Hitbox>&& hb) :
			UIMenu(window, std::move(hb), futil::toString<T>, window.props.fontRegular(), window.props.defaultBackground(), false) {}
		UIMenu(UIMenu&& other) noexcept = default;

		inline const T* getSelectedItem() { return &this->rows[currentIndex]->item; }
		inline UIMenu& setItemFont(const FFont& itemFont) { return UIList<T>::setItemFont(itemFont), * this; }
		inline UIMenu& setLabelFunc(const func<const str(T&)>& labelFunc) { return UIList<T>::setLabelFunc(labelFunc), * this; }
		inline UIMenu& setLabelFunc(func<const str(T&)>&& labelFunc) { return UIList<T>::setLabelFunc(move(labelFunc)), * this; }
		inline UIMenu& setMaxRows(int rows) { return UIList<T>::setMaxRows(rows), * this; }
		inline UIMenu& setOnChange(const func<void(const T*)>& onChange) { return this->onChange = onChange, *this; }
		inline UIMenu& setOnChange(func<void(const T*)>&& onChange) { return this->onChange = move(onChange), *this; }

		void select(int ind);
		void select(T& item);
		void selectRow(UIEntry<T>& entry) override;
	protected:
		int currentIndex = 0;

		virtual UIEntry<T>* makeRow(const T& item, int i) override;
	private:
		func<void(const T*)> onChange;

		void changeEvent();
	};

	// Selects the row matching the given index
	template<typename T> void UIMenu<T>::select(int ind)
	{
		currentIndex = ind;
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(row->index == ind); }
	}

	// Selects the row matching the given item
	template<typename T> void UIMenu<T>::select(T& item)
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
	template<typename T> void UIMenu<T>::selectRow(UIEntry<T>& entry)
	{
		currentIndex = entry.index;
		for (const uptr<UIEntry<T>>& row : this->rows) { row->updateSelectStatus(row->index == entry.index); }
		changeEvent();
	}

	template<typename T> UIEntry<T>* UIMenu<T>::makeRow(const T& item, int i)
	{
		UIEntry<T>* entry = new UIEntry<T>(item,
			i,
			[this](UIEntry<T>& p) { this->selectRow(p); },
			make_unique<RelativeHitbox>(*this->hb),
			this->getItemFont(),
			this->labelFunc(item),
			EMPTY,
			EMPTY);
		entry->setHbExactSizeY(this->win.renderScale(64));
		return entry;
	}

	template<typename T> void UIMenu<T>::changeEvent()
	{
		if (onChange) {
			onChange(getSelectedItem());
		}
	}
}