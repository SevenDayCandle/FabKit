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
		virtual UIHoverable& addElement(uptr<UIHoverable> element);
		virtual bool isHovered() override;
		virtual void renderImpl() override;
		virtual UIHoverable& stackElementXDir(uptr<UIHoverable> element, float spacing, float start);
		virtual UIHoverable& stackElementYDir(uptr<UIHoverable> element, float spacing, float start);
		virtual void updateImpl() override;
	protected:
		vec<uptr<UIHoverable>> elements;
	};

	UIHoverable& UICanvas::addElement(uptr<UIHoverable> element)
	{
		elements.push_back(std::move(element));
		return *element;
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
	UIHoverable& UICanvas::stackElementXDir(uptr<UIHoverable> element, float spacing, float start = 0) {
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIHoverable& last = *elements[elements.size() - 2];
			Hitbox& lhb = *(last.hb);
			float xOff = lhb.getOffsetX() + lhb.width + spacing;
			float yOff = lhb.getOffsetY();

			if (xOff > hb->width) {
				xOff = start;
				yOff = yOff - element->hb->height - spacing;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
		return *element;
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would be less than 0, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing and start should both be scaled by renderScale
	 */
	UIHoverable& UICanvas::stackElementYDir(uptr<UIHoverable> element, float spacing, float start = 0) {
		elements.push_back(std::move(element));
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			UIHoverable& last = *elements[elements.size() - 2];
			Hitbox& lhb = *(last.hb);
			float xOff = lhb.getOffsetX();
			float yOff = lhb.getOffsetY() - element->hb->height - spacing;

			if (yOff < 0) {
				xOff = xOff + lhb.width + spacing;
				yOff = start;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
		return *element;
	}

	// Update inner children; deliberately avoid updating own hb
	void UICanvas::updateImpl()
	{
		for (const uptr<UIHoverable>& element : elements) {
			element->update();
		}
	}
}