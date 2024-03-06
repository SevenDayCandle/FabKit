export module fbc.uiCanvas;

import fbc.futil;
import fbc.hitbox;
import fbc.uiHoverable;
import std;

export namespace fbc::ui {

	export class UICanvas : public UIHoverable {
	public:
		UICanvas(ui::Hitbox* hb) : UIHoverable(hb) {}
		~UICanvas() override {}

		inline void addElement(sptr<UIHoverable> element) { elements.push_back(element); }
		inline void clear() { elements.clear(); }
		virtual bool isHovered() override;
		virtual void renderImpl() override;
		virtual void stackElementXDir(sptr<UIHoverable> element, float spacing, float start);
		virtual void stackElementYDir(sptr<UIHoverable> element, float spacing, float start);
		virtual void updateImpl() override;
	protected:
		vec<sptr<UIHoverable>> elements;
	};

	// Is considered hovered if any child element is hovered; own hitbox is ignored
	bool UICanvas::isHovered() {
		return any(elements, [](const sptr<UIHoverable>& i) { return i->isHovered(); });
	}

	void UICanvas::renderImpl()
	{
		for (const sptr<UIHoverable>& element : elements) {
			element->render();
		}
	}

	/* Add an element to the canvas to the right of the last element placed with X offset defined by spacing.
	 * If the element's X endpoint would exceed the width of this hb, it gets moved below the last element at the X offset defined by start
	 * Spacing and start should both be scaled by renderScale
	 */
	void UICanvas::stackElementXDir(sptr<UIHoverable> element, float spacing, float start = 0) {
		elements.push_back(element);
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			const sptr<UIHoverable> last = elements[elements.size() - 2];
			Hitbox& lhb = *(last->hb);
			float xOff = lhb.getOffsetX() + lhb.width + spacing;
			float yOff = lhb.getOffsetY();

			if (xOff > hb->width) {
				xOff = start;
				yOff = yOff - element->hb->height - spacing;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
	}

	/* Add an element to the canvas below the last element placed with Y offset defined by spacing.
	 * If the element's Y endpoint would be less than 0, it gets moved to the right of the last element at the Y offset defined by start
	 * Spacing and start should both be scaled by renderScale
	 */
	void UICanvas::stackElementYDir(sptr<UIHoverable> element, float spacing, float start = 0) {
		elements.push_back(element);
		// Only actually do positioning if there is a previous element to reference
		if (elements.size() > 1) {
			sptr<UIHoverable> last = elements[elements.size() - 2];
			Hitbox& lhb = *(last->hb);
			float xOff = lhb.getOffsetX();
			float yOff = lhb.getOffsetY() - element->hb->height - spacing;

			if (yOff < 0) {
				xOff = xOff + lhb.width + spacing;
				yOff = start;
			}

			lhb.setOffsetPos(xOff, yOff);
		}
	}

	// Update inner children; deliberately avoid updating own hb
	void UICanvas::updateImpl()
	{
		for (const sptr<UIHoverable>& element : elements) {
			element->update();
		}
	}
}