export module fbc.TextInfo;

import fbc.FFont;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font, strv text = "", sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), text(text), color(color), colorOutline(colorOutline) {
			// TODO remove constructor method
			refreshCache();
		}
		virtual ~TextInfo() = default;

		inline float getTextHeight() const { return cache.h; }
		inline float getTextWidth() const { return cache.w; }
		inline float getTextXPos() const { return cache.x; }
		inline float getTextYPos() const { return cache.y; }
		inline strv getText() const { return text; }
		inline void refreshCache() { updateCache(this->text, this->color, this->colorOutline); }

		void drawText() const;
		void drawText(float offX, float offY) const;
		TextInfo& set(strv text, sdl::Color color);
		TextInfo& set(strv text, sdl::Color color, sdl::Color colorOutline);
		TextInfo& set(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		TextInfo& setColor(sdl::Color color);
		TextInfo& setColorOutline(sdl::Color colorOutline);
		TextInfo& setFont(const FFont& font);
		TextInfo& setPos(float x, float y);
		TextInfo& setText(strv text);
	protected:
		FFont& font;
		str text;
		sdl::Color color = sdl::COLOR_WHITE;
		sdl::Color colorOutline = sdl::COLOR_BLACK;

		inline virtual bool hasCache() { return cache.texture != nullptr; }
		inline virtual int getLimitWidth() { return 0; }
		inline void updateCache(strv text) { updateCache(text, this->color, this->colorOutline); }
		inline void updateCache(strv text, const sdl::Color& color) { updateCache(text, color, this->colorOutline); }
		virtual void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline);

		void unloadCache();
	private:
		sdl::FontRender cache = { 0, 0, 0, 0, nullptr };
	};

	void TextInfo::drawText() const
	{
		if (cache.texture) {
			sdl::renderCopy(cache.texture, nullptr, &cache);
		}
	}

	void TextInfo::drawText(float offX, float offY) const
	{
		if (cache.texture) {
			sdl::RectF textRect = { cache.x + offX, cache.y + offY, cache.w, cache.h };
			sdl::renderCopy(cache.texture, nullptr, &textRect);
		}
	}

	TextInfo& TextInfo::set(strv text, sdl::Color color)
	{
		this->text = text;
		this->color = color;
		refreshCache();
		return *this;
	}


	TextInfo& TextInfo::set(strv text, sdl::Color color, sdl::Color colorOutline)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		refreshCache();
		return *this;
	}

	TextInfo& TextInfo::set(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		this->font = font;
		refreshCache();
		return *this;
	}

	TextInfo& TextInfo::setColor(sdl::Color color)
	{
		this->color = color;
		refreshCache();
		return *this;
	}

	TextInfo& TextInfo::setColorOutline(sdl::Color colorOutline)
	{
		this->colorOutline = colorOutline;
		refreshCache();
		return *this;
	}

	TextInfo& TextInfo::setFont(const FFont& font)
	{
		this->font = font;
		refreshCache();
		return *this;
	}

	TextInfo& TextInfo::setPos(float x, float y)
	{
		cache.x = x;
		cache.y = y;
		return *this;
	}

	TextInfo& TextInfo::setText(strv text)
	{
		this->text = text;
		refreshCache();
		return *this;
	}

	// Whenever any font parameter changes, renders must be updated
	void TextInfo::updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline)
	{
		unloadCache();

		if (text.empty()) {
			cache.texture = nullptr;
			cache.w = 0;
			cache.h = 0;
		}
		else {
			cache = font.makeTexture(text, getLimitWidth(), cache.x, cache.y, color, colorOutline);
		}
	}

	// Free existing texture
	void TextInfo::unloadCache()
	{
		if (cache.texture) {
			sdl::textureDestroy(cache.texture);
		}
	}
}