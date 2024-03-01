export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import raylib;

export namespace fbc {
	export class TextInfo {
	public:
		str text;
		sptr<fbc::FFont> font;
		raylib::Color color = raylib::White;
		float scale = 1;
		float spacing = 0;

		TextInfo() {
		}

		TextInfo(sptr<fbc::FFont> font): font(font) {
		}

		void drawText(raylib::Vector2 pos) {
			font->draw(text, pos, scale, spacing, color);
		}
		void drawText(float x, float y) {
			font->draw(text, x, y, scale, spacing, color);
		}
	};
}