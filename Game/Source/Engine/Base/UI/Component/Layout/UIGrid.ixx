export module fbc.UIGrid;

import fbc.CoreConfig;
import fbc.Hitbox;
import fbc.UIBase;
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import fbc.ScaleHitbox;
import std;

namespace fbc {

	export template <c_ext<UIBase> T> class UIGrid : public UIBase {
	public:
		class Iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			Iterator(typename vec<uptr<T>>::iterator it) : it(it) {}

			reference operator*() const { return *(*it); }
			pointer operator->() const { return (*it).get(); }

			Iterator& operator++() { return ++it, * this; }
			Iterator operator++(int) {
				Iterator tmp = *this;
				++it;
				return tmp;
			}

			friend bool operator==(const Iterator& a, const Iterator& b) { return a.it == b.it; }
			friend bool operator!=(const Iterator& a, const Iterator& b) { return a.it != b.it; }

		private:
			typename vec<uptr<T>>::iterator it;
		};

		UIGrid(Hitbox* hb, float spacingX = 100, float spacingY = 100, float scrollSpeed = 1) : UIBase(hb),
			spacingX(spacingX),
			spacingY(spacingY),
			scrollSpeed(scrollSpeed),
			scrollbar{ new ScaleHitbox(hb->w * 0.93f / cfg.renderScale(), hb->y + hb->h * 0.05f / cfg.renderScale(), 48, hb->h * 0.9f / cfg.renderScale()) } {
			scrollbar.enabled = false;
		}

		inline float getSpacingX() const { return spacingX; }
		inline float getSpacingY() const { return spacingY; }
		inline Iterator begin() { return Iterator(items.begin()); }
		inline Iterator end() { return Iterator(items.end()); }
		inline size_t size() { return items.size(); }

		template <c_itr<uptr<T>> Iterable> UIGrid& addItems(const Iterable& added);
		template <c_itr<uptr<T>> Iterable> UIGrid& setItems(const Iterable& items);
		UIGrid& addItem(uptr<T>&& item);
		UIGrid& setSpacing(float spacingX, float spacingY);
		UIGrid& setSpacingX(float spacingX);
		UIGrid& setSpacingY(float spacingY);
		virtual bool isHovered() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		float scrollSpeed = 1;
		float spacingX = 0;
		float spacingY = 0;
		UIVerticalScrollbar scrollbar;
		vec<uptr<T>> items;

		void updateItemOffsets();
		void updateItemOffsets(int begin, int end);
	};

	template<c_ext<UIBase> T> bool UIGrid<T>::isHovered()
	{
		return std::ranges::any_of(items, [](const uptr<T>& i) { return i->isHovered(); });
	}

	// Updates the dimensions of all children too
	template<c_ext<UIBase> T> void UIGrid<T>::refreshDimensions()
	{
		UIBase::refreshDimensions();
		for (const uptr<T>& element : items) {
			element->refreshDimensions();
		}
		scrollbar.refreshDimensions();
	}

	template<c_ext<UIBase> T> void UIGrid<T>::renderImpl()
	{
		for (const uptr<T>& item : items) {
			item->render();
		}
		scrollbar.render();
	}

	template<c_ext<UIBase> T> void UIGrid<T>::updateImpl()
	{
		UIBase::updateImpl();
		for (const uptr<T>& item : items) {
			item->update();
		}
		scrollbar.update();
	}

	// Updates the positions of ALL items in the grid, and shows the scrollbar if any of them would extend outside of the grid
	template<c_ext<UIBase> T> void UIGrid<T>::updateItemOffsets()
	{
		float sx = cfg.renderScale(spacingX);
		float sy = cfg.renderScale(spacingY);
		float x = hb->x;
		float y = hb->y;
		for (const uptr<T>& item : items) {
			item->hb->setExactPos(x, y);

			x += sx;
			if (x >= hb->x + hb->w) {
				x = hb->x;
				y += sy;
			}
		}

		scrollbar.enabled = y > hb->y + hb->h;
	}

	// Updates the positions of items from index begin (inclusive) to index end (exclusive), and shows the scrollbar if any of them would extend outside of the grid
	template<c_ext<UIBase> T> void UIGrid<T>::updateItemOffsets(int begin, int end) {
		float sx = cfg.renderScale(spacingX);
		float sy = cfg.renderScale(spacingY);
		int rowsize = hb->w / sx;
		int xP = begin % rowsize;
		int yP = begin / rowsize; // Intentional integer division in parentheses to ensure that this multiplier rounds down
		float x = hb->x + sx * xP;
		float y = hb->y + sy * yP;
		for (int i = begin; i < end; ++i) {
			items[i]->hb->setExactPos(x, y);

			x += sx;
			if (x >= hb->x + hb->w) {
				x = hb->x;
				y += sy;
			}
		}

		scrollbar.enabled = y > hb->y + hb->h;
	}

	// Add a singular item to the list
	template<c_ext<UIBase> T> UIGrid<T>& UIGrid<T>::addItem(uptr<T>&& item)
	{
		this->items.push_back(std::move(item));
		updateItemOffsets(this->items.size() - 1, this->items.size());
		return *this;
	}

	// Update the spacing between items
	template<c_ext<UIBase> T>UIGrid<T>& UIGrid<T>::setSpacing(float spacingX, float spacingY) {
		this->spacingX = spacingX;
		this->spacingY = spacingY;
		updateItemOffsets();
		return *this;
	}

	// Update the X spacing between items
	template<c_ext<UIBase> T>UIGrid<T>& UIGrid<T>::setSpacingX(float spacingX) {
		this->spacingX = spacingX;
		updateItemOffsets();
		return *this;
	}

	// Update the Y spacing between items
	template<c_ext<UIBase> T>UIGrid<T>& UIGrid<T>::setSpacingY(float spacingY) {
		this->spacingY = spacingY;
		updateItemOffsets();
		return *this;
	}

	// Appends items to the end of the grid
	template<c_ext<UIBase> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::addItems(const Iterable& added) {
		int a = this->items.size();
		this->items.insert(this->items.end(),
			std::make_move_iterator(added.begin()),
			std::make_move_iterator(added.end()));
		int b = this->items.size();
		updateItemOffsets(a, b);
		return *this;
	}

	// Replaces the contents of the grid with the incoming items
	template<c_ext<UIBase> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::setItems(const Iterable& items)
	{
		this->items = std::move(items);
		updateItemOffsets();
		return *this;
	}
}