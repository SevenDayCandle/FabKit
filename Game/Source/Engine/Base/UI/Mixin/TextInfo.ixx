export module fbc.TextInfo;

import fbc.FFont;
import fbc.FUtil;
import fbc.ImageDrawable;
import sdl;

// TODO directly extend imageDrawable
namespace fbc {
	export class TextInfo {
	public:
		TextInfo(FFont& font, strv text = "", sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), text(text), color(color), colorOutline(colorOutline) {
			refreshCache();
		}
		virtual ~TextInfo() = default;

		inline float getTextHeight() const { return cache.getHeight(); }
		inline float getTextWidth() const { return cache.getWidth(); }
		inline float getTextXPos() const { return texXPos; }
		inline float getTextYPos() const { return texYPos; }
		inline strv getText() const { return text; }
		inline void refreshCache() { updateCache(this->text, this->color, this->colorOutline); }

		void drawText(sdl::SDLBatchRenderPass&, float winW, float winH, float offX, float offY, const sdl::Color* color = &sdl::COLOR_STANDARD);
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
		sdl::Color color = sdl::COLOR_STANDARD;
		sdl::Color colorOutline = sdl::COLOR_BLACK;

		inline virtual bool hasCache() { return cache; }
		inline virtual int getLimitWidth() { return 0; }
		inline void updateCache(strv text) { updateCache(text, this->color, this->colorOutline); }
		inline void updateCache(strv text, const sdl::Color& color) { updateCache(text, color, this->colorOutline); }
		virtual void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline);

		void unloadCache();
	private:
		ImageDrawable cache;
		int texXPos;
		int texYPos;
	};

	void TextInfo::drawText(sdl::SDLBatchRenderPass& rp, float winW, float winH, float offX, float offY, const sdl::Color* color)
	{
		if (cache) {
			cache.draw(rp, texXPos + offX, texYPos + offY, cache.getWidth(), cache.getHeight(), winW, winH, 0, color);
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
		texXPos = x;
		texYPos = y;
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
			cache = ImageDrawable();
		}
		else {
			cache = font.makeTexture(text, getLimitWidth(), color, colorOutline);
		}
	}

	// Free existing texture
	void TextInfo::unloadCache()
	{
		cache = ImageDrawable();
	}
}