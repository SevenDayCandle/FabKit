export module fbc.UICanvas;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIBase;
import std;

export namespace fbc {

	export class UICanvas : public UIBase {
	public:
		UICanvas(Hitbox* hb) : UIBase(hb) {}
		UICanvas(uptr<Hitbox>&& hb) : UIBase(std::move(hb)) {}
		~UICanvas() override {}

		inline void clear() { elements.clear(); }

		template<typename T> requires std::is_base_of_v<UIBase, T> T& addElement(uptr<T>&& element);
		template<typename T> requires std::is_base_of_v<UIBase, T> T& stackElementXDir(uptr<T>&& element, float spacing = 8, float yOff = 0);
		template<typename T> requires std::is_base_of_v<UIBase, T> T& stackElementYDir(uptr<T>&& element, float spacing = 8, float xOff = 0);
		UIBase* getLastItem() const;
		virtual bool isHovered() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		vec<uptr<UIBase>> elements;
	};

	// Add a singular element to the canvas
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::addElement(uptr<T>&& element)
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
		return futil::any(elements, [](const uptr<UIBase>& i) { return i->isHovered(); });
	}

	// Updates the dimensions of all children too
	void UICanvas::refreshDimensions()
	{
		UIBase::refreshDimensions();
		for (const uptr<UIBase>& element : elements) {
			element->refreshDimensions();
		}
	}

	void UICanvas::renderImpl()
	{
		for (const uptr<UIBase>& element : elements) {
			element->render();
		}
	}

	/* Add an element to the canvas to the right of the last element placed with X offset defined by spacing.
	 * If the element's X endpoint would exceed the width of this hb, it gets moved below the last element at the X offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::stackElementXDir(uptr<T>&& element, float spacing, float yOff) {
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

			ref.hb->setExactPos(xPos, yPos);
		}
		return ref;
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would exceed the height of this hb, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing will automatically be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIBase, T> T& UICanvas::stackElementYDir(uptr<T>&& element, float spacing, float xOff) {
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

			ref.hb->setExactPos(xPos, yPos);
		}
		return ref;
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