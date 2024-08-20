export module fbc.TextDrawable;

import fbc.FFont;
import fbc.FUtil;
import fbc.ImageDrawable;
import sdl;

// TODO directly extend imageDrawable
namespace fbc {
	export class TextDrawable : public ImageDrawable {
	public:
		TextDrawable(FFont& font, strv text = "", float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), textW(w), text(text), color(color), colorOutline(colorOutline) {
			reload();
		}
		virtual ~TextDrawable() = default;

		inline bool empty() const { return text.empty(); }
		inline FFont& getFont() const { return font; }
		inline float getPosX() const { return posX; }
		inline float getPosY() const { return posY; }
		inline size_t getTextLen() const { return text.size(); }
		inline strv getText() const { return text; }
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) { draw(rp, x, y, texW, texH, winW, winH, rotZ, tint, pipeline); }

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
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
		TextDrawable& setWidth(float w);
		TextDrawable& textErase(size_t pos, size_t count);
		TextDrawable& textInsert(size_t pos, const char* text);
	private:
		FFont& font;
		int posX;
		int posY;
		int textW = 0;
		str text;
		sdl::Color color = sdl::COLOR_STANDARD;
		sdl::Color colorOutline = sdl::COLOR_BLACK;
	};

	void TextDrawable::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline)
	{
		if (texture) {
			ImageDrawable::draw(rp, x, y, w, h, winW, winH, rotZ, tint, pipeline);
		}
	}

	void TextDrawable::reload() const
	{
		sdl::GpuCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		sdl::GpuCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
		reload(copyPass);
		sdl::gpuEndCopyPass(copyPass);
		sdl::gpuSubmit(uploadCmdBuf);
	}

	void TextDrawable::reload(sdl::GpuCopyPass* copyPass) const
	{
		sdl::Surface* surface = font.makeSurface(text, textW, color, colorOutline);
		sdl::GpuTexture* fontTex = sdl::runner::uploadTexture(copyPass, surface);
		sdl::surfaceDestroy(surface);
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
		posX = x;
		posY = y;
		return *this;
	}

	TextDrawable& TextDrawable::setText(strv text)
	{
		this->text = text;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setWidth(float w) {
		this->textW = w;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::textErase(size_t pos, size_t count) {
		text.erase(pos, count);
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::textInsert(size_t pos, const char* add) {
		text.insert(pos, add);
		reload();
		return *this;
	}
}