export module fab.TextDrawable;

import fab.FFont;
import fab.FUtil;
import fab.Hitbox;
import fab.IDrawable;
import sdl.SDLBase;
import fab.BatchRenderPass;
import sdl.SDLRunner;

// TODO completely redo
/* Represents text to be rendered on the screen */
namespace fab {
	export class TextDrawable : public IDrawable {
	public:
		struct Props {
			FFont* font;
			int textW = 0;
			str text = "";
			sdl::Color color = sdl::COLOR_STANDARD;
			sdl::Color colorOutline = sdl::COLOR_BLACK;
		};

		TextDrawable(FFont& font, strv text = "", float w = 0, sdl::Color color = sdl::COLOR_STANDARD, sdl::Color colorOutline = sdl::COLOR_BLACK) : font(&font), textW(w), text(text), color(color), colorOutline(colorOutline) {
			TextDrawable::reload();
		}

		TextDrawable(const TextDrawable&) = delete;
		TextDrawable(TextDrawable&& other) noexcept : font(other.font), textW(other.textW), text(other.text), color(other.color), colorOutline(other.colorOutline) {}
		~TextDrawable() override = default;

		inline bool empty() const { return text.empty(); }
		inline bool loaded() const { return textObj; }
		inline FFont* getFont() const { return font; }
		inline str::const_iterator getTextBegin() const { return text.begin(); }
		inline str::const_iterator getTextEnd() const { return text.end(); }
		inline size_t getTextLen() const { return text.size(); }
		inline strv getText() const { return text; }

		inline void drawOffsetExact(BatchRenderPass& rp, Hitbox& hb, float xOff, float yOff, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawFull(rp, hb.x + xOff, hb.y + yOff, scX, scY, rotZ, tint, pipeline);
		}

		inline void drawOffsetScaled(BatchRenderPass& rp, Hitbox& hb, float xOff, float yOff, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawFull(rp, hb.x + hb.win.renderScale(xOff), hb.y + hb.win.renderScale(yOff), scX, scY, rotZ, tint, pipeline);
		}

		void dispose() override;
		void reload() const override;
		TextDrawable& set(strv text, sdl::Color color);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline);
		TextDrawable& set(strv text, sdl::Color color, sdl::Color colorOutline, FFont& font);
		TextDrawable& setColor(sdl::Color color);
		TextDrawable& setColorOutline(sdl::Color colorOutline);
		TextDrawable& setFont(FFont& font);
		TextDrawable& setText(strv text);
		TextDrawable& setWidth(float w);
		TextDrawable& textErase(size_t pos, size_t count);
		TextDrawable& textInsert(size_t pos, const char* text);

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	private:
		FFont* font;
		int textW = 0;
		mutable sdl::GPUAtlasDrawSequence* sequence;
		mutable sdl::Text* textObj;
		str text;
		sdl::Color color = sdl::COLOR_STANDARD;
		sdl::Color colorOutline = sdl::COLOR_BLACK;
	};

	void TextDrawable::dispose() {
		if (textObj) {
			sdl::textDestroy(textObj);
		}
	}

	void TextDrawable::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		float sX = scX * w;
		float sY = scY * h;
		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));

		// TODO account for shadows
		for (sdl::GPUAtlasDrawSequence* cur = sequence; cur != nullptr; cur = cur->next) {
			rp.bindTexture(cur->atlas_texture, sdl::runner::SAMPLER);
			sdl::Point* uv = cur->uv;
			sdl::Point* xy = cur->xy;

			// Each quad has four vertices; vertices 0 and 2 are always diagonal so you can get the region size from their difference
			for (int i = 0; i < cur->num_vertices; i += 4) {
				int u = uv[i].x;
				int v = uv[i].y;
				sdl::Point& diag = uv[i + 2];
				rp.pushVertexData({
					.texInd = 0,
					.coord = BatchRenderPass::makeCoord(u, v, diag.x - u, diag.y - v),
					.color = *tint,
					.transform = BatchRenderPass::makeTransform(tX + xy[i].x, tY + xy[i].x, sX, sY, rotZ)
				});
			}
		}
	}

	void TextDrawable::reload() const {
		if (textObj) {
			sdl::textDestroy(textObj);
		}
		textObj = sdl::runner::textCreate(*font, text);
		sequence = sdl::textGetSequence(textObj);
	}

	TextDrawable& TextDrawable::set(strv text, sdl::Color color) {
		this->text = text;
		this->color = color;
		reload();
		return *this;
	}


	TextDrawable& TextDrawable::set(strv text, sdl::Color color, sdl::Color colorOutline) {
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::set(strv text, sdl::Color color, sdl::Color colorOutline, FFont& font) {
		this->text = text;
		this->color = color;
		this->colorOutline = colorOutline;
		this->font = &font;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setColor(sdl::Color color) {
		this->color = color;
		return *this;
	}

	TextDrawable& TextDrawable::setColorOutline(sdl::Color colorOutline) {
		this->colorOutline = colorOutline;
		return *this;
	}

	TextDrawable& TextDrawable::setFont(FFont& font) {
		this->font = &font;
		reload();
		return *this;
	}

	TextDrawable& TextDrawable::setText(strv text) {
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
