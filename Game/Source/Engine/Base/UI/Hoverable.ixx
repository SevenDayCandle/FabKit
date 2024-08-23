export module fbc.Hoverable;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import std;

namespace fbc {
	export class Hoverable : public FWindow::Element {
	public:
		Hoverable(FWindow& window) : Element(window) {}
		virtual ~Hoverable() = default;

		inline virtual float getBeginX() { return getHb()->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return getHb()->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return getHb()->x + getHb()->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return getHb()->y + getHb()->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual bool isHovered() { return getHb()->isHovered(); }

		virtual Hitbox* getHb() = 0;
	};
}