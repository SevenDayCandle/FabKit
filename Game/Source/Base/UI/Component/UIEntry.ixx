export module fbc.uiEntry;

import fbc.hitbox;
import fbc.ffont;
import fbc.uiText;
import fbc.futil;

export namespace fbc {
	export template <typename T> class UIEntry : public UIText {
	public:
		UIEntry(T item, int index, fbc::Hitbox* hb, FFont& f, const str& text): item(item), index(index), UIText(hb, f, text) {}
		virtual ~UIEntry() {}

		T item;
		int index;
	};
}