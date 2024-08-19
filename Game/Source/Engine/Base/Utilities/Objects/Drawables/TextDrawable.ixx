export module fbc.TextDrawable;

import fbc.FFont;
import fbc.FUtil;
import fbc.ImageDrawable;
import sdl;

// TODO directly extend imageDrawable
namespace fbc {
	export class TextDrawable : public ImageDrawable {
	public:
		TextDrawable(FFont& font, strv text = "", sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), text(text), color(color), colorOutline(colorOutline) {
			reload();
		}
		virtual ~TextDrawable() = default;

		inline float getTextHeight() const { return cache.getHeight(); }
		inline float getTextWidth() const { return cache.getWidth(); }
		inline float getTextXPos() const { return texXPos; }
		inline float getTextYPos() const { return texYPos; }
		inline strv getText() const { return text; }

		void drawText(sdl::SDLBatchRenderPass&, float winW, float winH, float offX, float offY, const sdl::Color* color = &sdl::COLOR_STANDARD);
		void reload() const override;
		void reload(sdl::GpuCopyPass* copyPass) const;
		TextDrawable& set(strv text, sdl::Color color);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		TextDrawable& setColor(sdl::Color color);
		TextDrawable& setColorOutline(sdl::Color colorOutline);
		TextDrawable& setFont(const FFont& font);
		TextDrawable& setPos(float x, float y);
		TextDrawable& setText(strv text);
	private:
		FFont& font;
		int texXPos;
		int texYPos;
		str text;
		sdl::Color color = sdl::COLOR_STANDARD;
		sdl::Color colorOutline = sdl::COLOR_BLACK;
	};

	void TextDrawable::drawText(sdl::SDLBatchRenderPass& rp, float winW, float winH, float offX, float offY, const sdl::Color* color)
	{
		if (texture) {
			cache.draw(rp, texXPos + offX, texYPos + offY, cache.getWidth(), cache.getHeight(), winW, winH, 0, color);
		}
	}

	void TextDrawable::reload(sdl::GpuCopyPass* copyPass) const
	{
		sdl::Surface* surface = font.makeSurface(text, 0);
	}

	TextDrawable& TextDrawable::set(strv text, sdl::Color color)
	{
		this->text = text;
		this->color = color;
		reload();
		return *this;
	}


	TextDrawable& TextDrawable::set(strv text, sdl::Color color, sdl::Color colorOutline)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::set(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font)
	{
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		this->font = font;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setColor(sdl::Color color)
	{
		this->color = color;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setColorOutline(sdl::Color colorOutline)
	{
		this->colorOutline = colorOutline;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setFont(const FFont& font)
	{
		this->font = font;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setPos(float x, float y)
	{
		texXPos = x;
		texYPos = y;
		return *this;
	}

	TextDrawable& TextDrawable::setText(strv text)
	{
		this->text = text;
		reload();
		return *this;
	}
}