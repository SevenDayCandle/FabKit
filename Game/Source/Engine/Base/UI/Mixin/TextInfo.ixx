export module fbc.textInfo;

import fbc.ffont;
import fbc.futil;
import sdl;

export namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font, str text = "", sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), text(text), color(color), colorOutline(colorOutline) {
			updateCache();
		}
		virtual ~TextInfo() {}

		inline float getTextHeight() const { return cache.h; }
		inline float getTextWidth() const { return cache.w; }
		inline strv getText() { return text; }

		void drawText(float x, float y) const;
		TextInfo& set(str text, sdl::Color color);
		TextInfo& set(str text, sdl::Color color, sdl::Color colorOutline);
		TextInfo& set(str text, sdl::Color color, sdl::Color colorOutline, FFont& font);
		TextInfo& setColor(sdl::Color color);
		TextInfo& setColorOutline(sdl::Color colorOutline);
		TextInfo& setFont(FFont& font);
		TextInfo& setText(str text);
	protected:
		FFont& font;
		str text;
		sdl::Color color = sdl::COLOR_WHITE;
		sdl::Color colorOutline = sdl::COLOR_BLACK;

		inline virtual int getLimitWidth() { return 0; }
		inline void updateCache() { updateCache(this->text, this->color, this->colorOutline); }
		inline void updateCache(strv text) { updateCache(text, this->color, this->colorOutline); }
		inline void updateCache(strv text, const sdl::Color& color) { updateCache(text, color, this->colorOutline); }
		void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline);
	private:
		sdl::FontRender cache;
	};

	void TextInfo::drawText(float x, float y) const
	{
		if (cache.texture) {
			sdl::RectF textRect = { x, y, cache.w, cache.h };
			sdl::renderCopy(cache.texture, nullptr, &textRect);
		}
	}

	TextInfo& TextInfo::set(str text, sdl::Color color)
	{
		this->text = text;
		this->color = color;
		updateCache();
		return *this;
	}


	TextInfo& TextInfo::set(str text, sdl::Color color, sdl::Color colorOutline)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		updateCache();
		return *this;
	}

	TextInfo& TextInfo::set(str text, sdl::Color color, sdl::Color colorOutline, FFont& font)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		this->font = font;
		updateCache();
		return *this;
	}

	TextInfo& TextInfo::setColor(sdl::Color color)
	{
		this->color = color;
		updateCache();
		return *this;
	}

	TextInfo& TextInfo::setColorOutline(sdl::Color colorOutline)
	{
		this->colorOutline = colorOutline;
		updateCache();
		return *this;
	}

	TextInfo& TextInfo::setFont(FFont& font)
	{
		this->font = font;
		updateCache();
		return *this;
	}

	TextInfo& TextInfo::setText(str text)
	{
		this->text = text;
		updateCache();
		return *this;
	}

	// Whenever any font parameter changes, renders must be updated
	void TextInfo::updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline)
	{
		// Free existing texture
		if (cache.texture) {
			sdl::textureDestroy(cache.texture);
		}

		if (text.empty()) {
			cache = sdl::FontRender();
		}
		else {
			cache = font.makeTexture(text, getLimitWidth(), color, colorOutline);
		}
	}
}