export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import sdl;

export namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font) : font(font) {}
		TextInfo(FFont& font, str text) : font(font), text(text) {}
		virtual ~TextInfo() {}

		FFont& font;
		str text;
		sdl::Color color = sdl::WHITE;
		sdl::Color outline = sdl::BLACK;

		void drawText(float x, float y) {
			font.draw(text, x, y, color, outline);
		}
	};
}