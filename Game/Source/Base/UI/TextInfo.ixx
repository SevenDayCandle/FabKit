export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import raylib;

export namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font) : font(font) {}
		TextInfo(FFont& font, str text) : font(font), text(text) {}
		virtual ~TextInfo() {}

		FFont& font;
		str text;
		raylib::Color color = raylib::White;
		float scale = 1;
		float spacing = 0;

		void drawText(const raylib::Vector2& pos) {
			font.draw(text, pos, scale, spacing, color);
		}
		void drawText(float x, float y) {
			font.draw(text, x, y, scale, spacing, color);
		}
	};
}