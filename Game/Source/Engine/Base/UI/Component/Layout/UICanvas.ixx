export module fbc.UICanvas;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.UIBase;
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {

	export class UICanvas : public UIBase {
	public:
		class Iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = UIBase;
			using difference_type = std::ptrdiff_t;
			using pointer = UIBase*;
			using reference = UIBase&;

			Iterator(typename vec<uptr<UIBase>>::iterator it) : it(it) {}

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
			typename vec<uptr<UIBase>>::iterator it;
		};

		UICanvas(FWindow& window, Hitbox* hb) : UIBase(window, hb) {}
		UICanvas(FWindow& window, uptr<Hitbox>&& hb) : UIBase(window, std::move(hb)) {}
		~UICanvas() override {}

		inline bool empty() { return elements.empty(); }
		inline Iterator begin() { return Iterator(elements.begin()); }
		inline Iterator end() { return Iterator(elements.end()); }
		inline size_t size() const { return elements.size(); }
		inline void clear() { elements.clear(); }

		template<typename T> requires std::is_base_of_v<UIBase, T> T& add(uptr<T>&& element);
		template<typename T> requires std::is_base_of_v<UIBase, T> T& stackXDir(uptr<T>&& element, float spacing = 8, float yOff = 0);
		template<typename T> requires std::is_base_of_v<UIBase, T> T& stackYDir(uptr<T>&& element, float spacing = 8, float xOff = 0);
		template<typename T> requires std::is_base_of_v<UIBase, T> uptr<T> extract(T* item);
		UIBase* getLastItem() const;
		virtual bool isHovered() override;
		virtual bool remove(UIBase* item);
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	protected:
		vec<uptr<UIBase>> elements;
	};

	// Add a singular element to the canvas
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::add(uptr<T>&& element)
	{
		T& ref = *element;
		elements.push_back(std::move(element));
		return ref;
	}

	// Get the hb for the last item added into the list
	UIBase* UICanvas::getLastItem() const
	{
		if (elements.size() > 0) {
			return elements[elements.size() - 1].get();
		}
		return nullptr;
	}

	// Is considered hovered if any child element is hovered; own hitbox is ignored
	bool UICanvas::isHovered() {
		return std::ranges::any_of(elements, [](const uptr<UIBase>& i) { return i->isHovered(); });
	}

	// Updates the dimensions of all children too
	void UICanvas::refreshDimensions()
	{
		UIBase::refreshDimensions();
		for (const uptr<UIBase>& element : elements) {
			element->refreshDimensions();
		}
	}

	// Removes a specified element from the canvas. Return true if the element was erased
	bool UICanvas::remove(UIBase* item)
	{
		for (auto it = elements.begin(); it != elements.end(); ++it) {
			if (it->get() == item) {
				elements.erase(it);
				return true;
			}
		}
		return false;
	}

	void UICanvas::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		for (const uptr<UIBase>& element : elements) {
			element->render(rp);
		}
	}

	/* Add an element to the canvas to the right of the last element placed with X offset defined by spacing.
	 * If the element's X endpoint would exceed the width of this hb, it gets moved below the last element at the X offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::stackXDir(uptr<T>&& element, float spacing, float yOff) {
		float scaled = cfg.renderScale(spacing);
		T& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIBase& last = *elements[elements.size() - 2];
			float xPos = last.getEndX() + scaled;
			float yPos = last.getBeginY() + yOff;

			if (xPos > hb->x + hb->w) {
				xPos = hb->x;
				yPos = last.getEndY() + scaled + yOff;
			}

			ref.hb->setRealPos(xPos, yPos);
		}
		return ref;
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would exceed the height of this hb, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::stackYDir(uptr<T>&& element, float spacing, float xOff) {
		float scaled = cfg.renderScale(spacing);
		T& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIBase& last = *elements[elements.size() - 2];
			float xPos = last.getBeginX() + xOff;
			float yPos = last.getEndY() + scaled;

			if (yPos > hb->y + hb->h) {
				xPos = last.getEndX() + scaled + xOff;
				yPos = hb->y;
			}

			ref.hb->setRealPos(xPos, yPos);
		}
		return ref;
	}

	// Removes a specified element from the canvas and returns it
	template<typename T> requires std::is_base_of_v<UIBase, T> uptr<T> UICanvas::extract(T* item)
	{
		for (auto it = elements.begin(); it != elements.end(); ++it) {
			if (it->get() == item) {
				uptr<T> extracted(static_cast<T*>(it->release()));
				elements.erase(it);
				return extracted;
			}
		}
		return nullptr;
	}

	// Update inner children
	void UICanvas::updateImpl()
	{
		UIBase::updateImpl();
		for (const uptr<UIBase>& element : elements) {
			element->update();
		}
	}
}