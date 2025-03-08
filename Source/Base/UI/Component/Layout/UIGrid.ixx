export module fab.UIGrid;

import fab.FWindow;
import fab.Hitbox;
import fab.Hoverable;
import fab.FUtil;
import fab.ScaleHitbox;
import fab.UIBase;
import sdl.SDLBatchRenderPass;
import std;

namespace fab {
	export template <c_ext<Hoverable> T> class UIGrid : public UIBase {
	public:
		class ConstIterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = const T;
			using difference_type = std::ptrdiff_t;
			using pointer = const T*;
			using reference = const T&;

			ConstIterator(typename vec<uptr<T>>::const_iterator it) : it(it) {}

			reference operator*() const { return *(*it); }
			pointer operator->() const { return it->get(); }

			ConstIterator& operator++() { return ++it, * this; }
			ConstIterator operator++(int) {
				ConstIterator tmp = *this;
				++it;
				return tmp;
			}

			friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.it == b.it; }
			friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.it != b.it; }

		private:
			typename vec<uptr<T>>::const_iterator it;
		};

		class Iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			Iterator(typename vec<uptr<T>>::iterator it) : it(it) {}

			reference operator*() const { return *(*it); }
			pointer operator->() const { return it->get(); }

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

		UIGrid(FWindow& window, uptr<Hitbox>&& hb, float spacingX = 1, float spacingY = 1) : UIBase(window, move(hb)), intervalX(spacingX), intervalY(spacingY) {}
		UIGrid(UIGrid&& other) noexcept : UIBase(other.win, move(other.hb)), intervalX(other.intervalX), intervalY(other.intervalY), items(move(other.items)) {}

		inline ConstIterator begin() const { return ConstIterator(items.cbegin()); }
		inline ConstIterator end() const { return ConstIterator(items.cend()); }
		inline float getIntervalX() const { return intervalX; }
		inline float getIntervalY() const { return intervalY; }
		inline float updateItemOffsets() { return updateItemOffsets(0, items.size()); }
		inline Iterator begin() { return Iterator(items.begin()); }
		inline Iterator end() { return Iterator(items.end()); }
		inline size_t size() const { return items.size(); }
		inline void clear() { items.clear(); }
		template<typename... Args> requires std::constructible_from<T, FWindow&, Args&&...> inline T& addNew(Args&&... args) { return add(create<T>(forward<Args>(args)...)); };
		template<c_ext<T> U, typename... Args> requires std::constructible_from<U, FWindow&, Args&&...> inline U& addNew(Args&&... args) { return add(create<U>(forward<Args>(args)...)); };

		template <c_itr<uptr<T>> Iterable> UIGrid& addItems(const Iterable& added);
		template <c_itr<uptr<T>> Iterable> UIGrid& setItems(const Iterable& items);
		T& add(uptr<T>&& item);
		UIGrid& autosetInterval(float spacingX = 0, float spacingY = 0);
		UIGrid& setInterval(float spacingX, float spacingY);
		UIGrid& setIntervalX(float spacingX);
		UIGrid& setIntervalY(float spacingY);
		uptr<T> extract(T* item);
		T* at(int index) const;
		T* back() const;
		virtual bool isHovered() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		float intervalX = 0;
		float intervalY = 0;
		vec<uptr<T>> items;

		virtual float updateItemOffsets(int begin, int end);
	};

	template<c_ext<Hoverable> T> bool UIGrid<T>::isHovered()
	{
		return std::ranges::any_of(items, [](const uptr<T>& i) { return i->isHovered(); });
	}

	// Updates the dimensions of all children too
	template<c_ext<Hoverable> T> void UIGrid<T>::refreshDimensions()
	{
		UIBase::refreshDimensions();
		for (const uptr<T>& element : items) {
			element->refreshDimensions();
		}
	}

	template<c_ext<Hoverable> T> void UIGrid<T>::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		for (const uptr<T>& item : items) {
			item->render(rp);
		}
	}

	template<c_ext<Hoverable> T> void UIGrid<T>::updateImpl()
	{
		UIBase::updateImpl();
		for (const uptr<T>& item : items) {
			item->update();
		}
	}

	// Updates the positions of items from index begin (inclusive) to index end (exclusive), and shows the scrollbar if any of them would extend outside of the grid
	template<c_ext<Hoverable> T> float UIGrid<T>::updateItemOffsets(int begin, int end) {
		float sx = win.renderScale(intervalX);
		float sy = win.renderScale(intervalY);
		int rowsize = std::max(1.0f, hb->w / sx);
		int xP = begin % rowsize;
		int yP = begin / rowsize; // Intentional integer division in parentheses to ensure that this multiplier rounds down
		float x = hb->x + sx * xP;
		float y = hb->y + sy * yP;
		for (int i = begin; i < end; ++i) {
			items[i]->getHb()->setRealPos(x, y);

			x += sx;
			if (x > hb->x + hb->w) {
				x = hb->x;
				y += sy;
			}
		}
		return y;
	}

	// Add a singular item to the list
	template<c_ext<Hoverable> T> T& UIGrid<T>::add(uptr<T>&& item)
	{
		T& ref = *item;
		this->items.push_back(std::move(item));
		updateItemOffsets(this->items.size() - 1, this->items.size());
		return ref;
	}

	// Sets up an interval between items based on the hitbox size of the first item. Does nothing if there are no items
	template<c_ext<Hoverable> T> UIGrid<T>& UIGrid<T>::autosetInterval(float spacingX, float spacingY) {
		if (this->items.size() > 0) {
			Hitbox& firsth = *this->items[0]->getHb();
			setInterval(firsth.getScaledOffSizeX() + spacingX, firsth.getScaledOffSizeY() + spacingY);
		}
		return *this;
	}

	// Update the starting interval between items. Note that this interval does not respect the actual sizes of UI elements and can result in overlap if it is smaller than the UI size; use autosetInterval if you want to guarantee avoidance of overlap
	template<c_ext<Hoverable> T> UIGrid<T>& UIGrid<T>::setInterval(float spacingX, float spacingY) {
		this->intervalX = spacingX;
		this->intervalY = spacingY;
		updateItemOffsets();
		return *this;
	}

	// Update the starting X interval between items. Note that this interval does not respect the actual sizes of UI elements and can result in overlap if it is smaller than the UI size; use autosetInterval if you want to guarantee avoidance of overlap
	template<c_ext<Hoverable> T> UIGrid<T>& UIGrid<T>::setIntervalX(float spacingX) {
		this->intervalX = spacingX;
		updateItemOffsets();
		return *this;
	}

	// Update the starting Y interval between items. Note that this interval does not respect the actual sizes of UI elements and can result in overlap if it is smaller than the UI size; use autosetInterval if you want to guarantee avoidance of overlap
	template<c_ext<Hoverable> T> UIGrid<T>& UIGrid<T>::setIntervalY(float spacingY) {
		this->intervalY = spacingY;
		updateItemOffsets();
		return *this;
	}

	// Removes a specified element and returns it
	template<c_ext<Hoverable> T> uptr<T> UIGrid<T>::extract(T* item) {
		for (auto it = items.begin(); it != items.end(); ++it) {
			if (it->get() == item) {
				uptr<T> extracted(it->release());
				items.erase(it);
				return extracted;
			}
		}
		return nullptr;
	}

	// Get the item at the given index if it exists
	template<c_ext<Hoverable> T> T* UIGrid<T>::at(int index) const {
		if (items.size() > index) {
			return items[index].get();
		}
		return nullptr;
	}

	// Get the last item added into the list if it exists
	template<c_ext<Hoverable> T> T* UIGrid<T>::back() const {
		if (items.size() > 0) {
			return items[items.size() - 1].get();
		}
		return nullptr;
	}

	// Appends items to the end of the grid
	template<c_ext<Hoverable> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::addItems(const Iterable& added) {
		int a = this->items.size();
		this->items.insert(this->items.end(),
			std::make_move_iterator(added.begin()),
			std::make_move_iterator(added.end()));
		int b = this->items.size();
		updateItemOffsets(a, b);
		return *this;
	}

	// Replaces the contents of the grid with the incoming items
	template<c_ext<Hoverable> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::setItems(const Iterable& items)
	{
		this->items = std::move(items);
		updateItemOffsets();
		return *this;
	}
}