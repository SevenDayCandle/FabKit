export module fbc.uiCanvas;

import fbc.futil;
import fbc.hitbox;
import fbc.uiHoverable;
import std;

export namespace fbc {

	export class UICanvas : public UIHoverable {
	public:
		UICanvas(Hitbox* hb) : UIHoverable(hb) {}
		~UICanvas() override {}

		inline void clear() { elements.clear(); }

		template<typename T> requires std::is_base_of_v<UIHoverable, T> T& addElement(uptr<T>&& element);
		template<typename T> requires std::is_base_of_v<UIHoverable, T> T& stackElementXDir(uptr<T>&& element, float spacing = 0, float start = 0);
		template<typename T> requires std::is_base_of_v<UIHoverable, T> T& stackElementYDir(uptr<T>&& element, float spacing = 0, float start = 0);
		virtual bool isHovered() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		vec<uptr<UIHoverable>> elements;
	};

	template<typename T> requires std::is_base_of_v<UIHoverable, T> T& UICanvas::addElement(uptr<T>&& element)
	{
		T& ref = *element;
		elements.push_back(std::move(element));
		return ref;
	}

	// Is considered hovered if any child element is hovered; own hitbox is ignored
	bool UICanvas::isHovered() {
		return futil::any(elements, [](const uptr<UIHoverable>& i) { return i->isHovered(); });
	}

	void UICanvas::renderImpl()
	{
		for (const uptr<UIHoverable>& element : elements) {
			element->render();
		}
	}

	/* Add an element to the canvas to the right of the last element placed with X offset defined by spacing.
	 * If the element's X endpoint would exceed the width of this hb, it gets moved below the last element at the X offset defined by start
	 * Spacing and start should both be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIHoverable, T> T& UICanvas::stackElementXDir(uptr<T>&& element, float spacing, float start) {
		T& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIHoverable& last = *elements[elements.size() - 2];
			Hitbox& lhb = *(last.hb);
			float xOff = lhb.getOffsetX() + lhb.w + spacing;
			float yOff = lhb.getOffsetY();

			if (xOff > hb->w) {
				xOff = start;
				yOff = yOff - element->hb->h - spacing;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
		return ref;
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would exceed the height of this hb, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing and start should both be scaled by renderScale
	 */
	template<typename T> requires std::is_base_of_v<UIHoverable, T> T& UICanvas::stackElementYDir(uptr<T>&& element, float spacing, float start) {
		T& ref = *element;
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIHoverable& last = *elements[elements.size() - 2];
			Hitbox& lhb = *(last.hb);
			float xOff = lhb.getOffsetX();
			float yOff = lhb.getOffsetY() - element->hb->h - spacing;

			if (yOff > hb->h) {
				xOff = xOff + lhb.w + spacing;
				yOff = start;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
		return ref;
	}

	// Update inner children; deliberately avoid updating own hb
	void UICanvas::updateImpl()
	{
		for (const uptr<UIHoverable>& element : elements) {
			element->update();
		}
	}
}