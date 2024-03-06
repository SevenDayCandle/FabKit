export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import raylib;

export namespace fbc::ui {
	export class ITextInfo {
	public:
		ITextInfo() {}
		ITextInfo(sptr<fbc::FFont> font) : font(font) {}
		virtual ~ITextInfo() {}

		str text;
		sptr<fbc::FFont> font;
		raylib::Color color = raylib::White;
		float scale = 1;
		float spacing = 0;

		void drawText(const raylib::Vector2& pos) {
			font->draw(text, pos, scale, spacing, color);
		}
		void drawText(float x, float y) {
			font->draw(text, x, y, scale, spacing, color);
		}
	};
}