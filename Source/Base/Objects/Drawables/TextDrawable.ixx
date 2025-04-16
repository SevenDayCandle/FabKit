export module fab.TextDrawable;

import fab.FFont;
import fab.FUtil;
import fab.Hitbox;
import fab.ImageDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

/* Represents text to be rendered on the screen */
namespace fab {
	export class TextDrawable : public ImageDrawable {
	public:
		TextDrawable(FFont& font, strv text = "", float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(font), textW(w), text(text), color(color), colorOutline(colorOutline) {
			TextDrawable::reload();
		}
		TextDrawable(const TextDrawable&) = delete;
		TextDrawable(TextDrawable&& other) noexcept : ImageDrawable(move(other)), font(other.font), textW(other.textW), text(other.text), color(other.color), colorOutline(other.colorOutline) {}
		virtual ~TextDrawable() = default;

		inline bool empty() const { return text.empty(); }
		inline FFont& getFont() const { return font; }
		inline str::const_iterator getTextBegin() const { return text.begin(); }
		inline str::const_iterator getTextEnd() const { return text.end(); }
		inline size_t getTextLen() const { return text.size(); }
		inline strv getText() const { return text; }
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			if (texture) {
				ImageDrawable::draw(rp, x, y, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
			}
		}
		inline void drawCentered(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			if (texture) {
				ImageDrawable::drawCentered(rp, x, y, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
			}
		}
		inline void drawOffsetExact(sdl::SDLBatchRenderPass& rp, Hitbox& hb, float xOff, float yOff, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawFull(rp, hb.x + xOff, hb.y + yOff, hb.win.getW(), hb.win.getH(), scX, scY, rotZ, tint, pipeline);
		}
		inline void drawOffsetScaled(sdl::SDLBatchRenderPass& rp, Hitbox& hb, float xOff, float yOff, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawFull(rp, hb.x + hb.win.renderScale(xOff), hb.y + hb.win.renderScale(yOff), hb.win.getW(), hb.win.getH(), scX, scY, rotZ, tint, pipeline);
		}

		void reload() const override;
		void reload(sdl::GPUCopyPass* copyPass) const;
		TextDrawable& set(strv text, sdl::Color color);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		TextDrawable& setColor(sdl::Color color);
		TextDrawable& setColorOutline(sdl::Color colorOutline);
		TextDrawable& setFont(const FFont& font);
		TextDrawable& setText(strv text);
		TextDrawable& setWidth(float w);
		TextDrawable& textErase(size_t pos, size_t count);
		TextDrawable& textInsert(size_t pos, const char* text);
	private:
		FFont& font;
		int textW = 0;
		str text;
		sdl::Color color = sdl::COLOR_STANDARD;
		sdl::Color colorOutline = sdl::COLOR_BLACK;
	};

	void TextDrawable::reload() const
	{
		sdl::GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
		reload(copyPass);
		sdl::gpuEndCopyPass(copyPass);
		sdl::gpuSubmit(uploadCmdBuf);
	}

	void TextDrawable::reload(sdl::GPUCopyPass* copyPass) const
	{
		if (texture) {
			sdl::runner::deviceReleaseTexture(texture);
			texture = nullptr;
		}
		sdl::Surface* surface = font.makeSurface(text, textW, color, colorOutline);
		if (surface) {
			texH = surface->h;
			texW = surface->w;
			texture = sdl::runner::uploadTexture(copyPass, surface);
			sdl::surfaceDestroy(surface);
		}
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