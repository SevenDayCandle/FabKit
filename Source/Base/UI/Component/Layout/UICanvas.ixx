export module fbc.UICanvas;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.Hoverable;
import fbc.UIBase;
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {
	export template<c_ext<Hoverable> T = Hoverable> class UICanvas : public UIBase {
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

		UICanvas(FWindow& window, uptr<Hitbox>&& hb) : UIBase(window, move(hb)) {}
		~UICanvas() override {}

		inline bool empty() { return elements.empty(); }
		inline Iterator begin() { return Iterator(elements.begin()); }
		inline Iterator end() { return Iterator(elements.end()); }
		inline size_t size() const { return elements.size(); }
		inline void clear() { elements.clear(); }
		template<c_ext<T> U, typename... Args> requires std::constructible_from<U, FWindow&, Args&&...> inline U& addNew(Args&&... args) { return add(create<U>(forward<Args>(args)...)); };

		template<c_ext<T> U = T> U& add(uptr<U>&& element);
		template<c_ext<T> U = T> U& stackXDir(uptr<U>&& element, float spacing = 8, float yOff = 0);
		template<c_ext<T> U = T> U& stackYDir(uptr<U>&& element, float spacing = 8, float xOff = 0);
		template<c_ext<T> U = T> uptr<U> extract(U* item);
		T* getLastItem() const;
		virtual bool isHovered() override;
		virtual bool remove(Hoverable* item);
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		vec<uptr<T>> elements;
	};

	// Add a singular element to the canvas
	template<c_ext<Hoverable> T> template<c_ext<T> U> U& UICanvas<T>::add(uptr<U>&& element)
	{
		U& ref = *element;
		elements.push_back(std::move(element));
		return ref;
	}

	// Get the hb for the last item added into the list
	template<c_ext<Hoverable> T> T* UICanvas<T>::getLastItem() const
	{
		if (elements.size() > 0) {
			return elements[elements.size() - 1].get();
		}
		return nullptr;
	}

	// Is considered hovered if any child element is hovered; own hitbox is ignored
	template<c_ext<Hoverable> T> bool UICanvas<T>::isHovered() {
		return std::ranges::any_of(elements, [](const uptr<T>& i) { return i->isHovered(); });
	}

	// Updates the dimensions of all children too
	template<c_ext<Hoverable> T> void UICanvas<T>::refreshDimensions()
	{
		UIBase::refreshDimensions();
		for (const uptr<T>& element : elements) {
			element->refreshDimensions();
		}
	}

	// Removes a specified element from the canvas. Return true if the element was erased
	template<c_ext<Hoverable> T> bool UICanvas<T>::remove(Hoverable* item)
	{
		for (auto it = elements.begin(); it != elements.end(); ++it) {
			if (it->get() == item) {
				elements.erase(it);
				return true;
			}
		}
		return false;
	}

	template<c_ext<Hoverable> T> void UICanvas<T>::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		for (const uptr<T>& element : elements) {
			element->render(rp);
		}
	}

	/* Add an element to the canvas to the right of the last element placed with X offset defined by spacing.
	 * If the element's X endpoint would exceed the width of this hb, it gets moved below the last element at the X offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<c_ext<Hoverable> T> template<c_ext<T> U> U& UICanvas<T>::stackXDir(uptr<U>&& element, float spacing, float yOff) {
		float scaled = win.renderScale(spacing);
		U& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			T& last = *elements[elements.size() - 2];
			float xPos = last.getEndX() + scaled;
			float yPos = last.getBeginY() + yOff;

			if (xPos > hb->x + hb->w) {
				xPos = hb->x;
				yPos = last.getEndY() + scaled + yOff;
			}

			ref.getHb()->setRealPos(xPos, yPos);
		}
		return ref;
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would exceed the height of this hb, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<c_ext<Hoverable> T> template<c_ext<T> U> U& UICanvas<T>::stackYDir(uptr<U>&& element, float spacing, float xOff) {
		float scaled = win.renderScale(spacing);
		U& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			T& last = *elements[elements.size() - 2];
			float xPos = last.getBeginX() + xOff;
			float yPos = last.getEndY() + scaled;

			if (yPos > hb->y + hb->h) {
				xPos = last.getEndX() + scaled + xOff;
				yPos = hb->y;
			}

			ref.getHb()->setRealPos(xPos, yPos);
		}
		return ref;
	}

	// Removes a specified element from the canvas and returns it
	template<c_ext<Hoverable> T> template<c_ext<T> U> uptr<U> UICanvas<T>::extract(U* item)
	{
		for (auto it = elements.begin(); it != elements.end(); ++it) {
			if (it->get() == item) {
				uptr<U> extracted(static_cast<U*>(it->release()));
				elements.erase(it);
				return extracted;
			}
		}
		return nullptr;
	}

	// Update inner children
	template<c_ext<Hoverable> T> void UICanvas<T>::updateImpl()
	{
		UIBase::updateImpl();
		for (const uptr<T>& element : elements) {
			element->update();
		}
	}
}