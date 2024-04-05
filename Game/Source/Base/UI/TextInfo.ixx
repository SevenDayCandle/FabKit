export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import sdl;

export namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font, str text = "", sdl::Color color = sdl::WHITE, sdl::Color colorOutline = sdl::BLACK) : font(font), text(text), color(color), colorOutline(colorOutline) {
			updateOutlineCache();
			updateTextCache();
		}
		virtual ~TextInfo() {}

		inline int getOutlineHeight() { return cacheOutline.h; }
		inline int getOutlineWidth() { return cacheOutline.w; }
		inline int getTextHeight() { return cacheText.h; }
		inline int getTextWidth() { return cacheText.w; }
		inline strv getText() { return text; }

		void drawText(float x, float y);
		TextInfo& setColor(sdl::Color color);
		TextInfo& setColorOutline(sdl::Color colorOutline);
		TextInfo& setFont(FFont& font);
		TextInfo& setText(str text);
	protected:
		FFont& font;
		str text;
		sdl::Color color = sdl::WHITE;
		sdl::Color colorOutline = sdl::BLACK;

		inline virtual int getWidth() { return 0; }
	private:
		FFontRender cacheOutline;
		FFontRender cacheText;

		void updateOutlineCache();
		void updateTextCache();
	};

	void TextInfo::drawText(float x, float y)
	{
		if (cacheOutline.texture) {
			sdl::RectF outlineRect = { x - font.getOutlineSize(), y - font.getOutlineSize(), cacheOutline.w, cacheOutline.h };
			sdl::renderCopy(cacheOutline.texture, nullptr, &outlineRect);
		}
		if (cacheText.texture) {
			sdl::RectF textRect = { x, y, cacheText.w, cacheText.h };
			sdl::renderCopy(cacheText.texture, nullptr, &textRect);
		}
	}

	TextInfo& TextInfo::setColor(sdl::Color color)
	{
		this->color = color;
		updateTextCache();
		return *this;
	}

	TextInfo& TextInfo::setColorOutline(sdl::Color colorOutline)
	{
		this->colorOutline = colorOutline;
		updateOutlineCache();
		return *this;
	}

	TextInfo& TextInfo::setFont(FFont& font)
	{
		this->font = font;
		updateTextCache();
		updateOutlineCache();
		return *this;
	}

	TextInfo& TextInfo::setText(str text)
	{
		this->text = text;
		updateTextCache();
		updateOutlineCache();
		return *this;
	}

	// Whenever font, text, or outline color change, outline render must be updated. Ignore outline if outline size is 0
	void TextInfo::updateOutlineCache()
	{
		if (text.empty() || font.getOutlineSize() <= 0) {
			cacheOutline = FFontRender();
		}
		else {
			cacheOutline = font.makeOutline(text, getWidth(), colorOutline);
		}
	}

	// Whenever font, text, or text color change, outline render must be updated
	void TextInfo::updateTextCache()
	{
		if (text.empty()) {
			cacheText = FFontRender();
		}
		else {
			cacheText = font.makeText(text, getWidth(), color);
		}
	}
}