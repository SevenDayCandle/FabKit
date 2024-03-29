export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import sdl;
import std;

export namespace fbc {
    const str FONT_REGULAR = "Resources/Fonts/Rubik-Regular.ttf";

    export struct FFontRender {
        sdl::Texture* texture;
        int w;
        int h;
    };

	export class FFont {
    public:
        FFont(str path, int size, int outlineSize): path(path), size(size), outlineSize(outlineSize) {
            reloadFont();
        }
        FFont(const FFont&) = delete;
        ~FFont() {
            // Unload font when destroyed
            if (font) {
                sdl::fontClose(font);
                font = nullptr;
            }
        }

        inline int getOutlineSize() { return outlineSize; }
        inline int getSize() { return size; }

        FFont& setOutlineSize(int size);
        FFont& setSize(int size);
        FFontRender makeOutline(strv text, uint32 w, sdl::Color color);
        FFontRender makeText(strv text, uint32 w, sdl::Color color);
        void dispose();
        void draw(strv text, float x, float y, uint32 w, sdl::Color color, sdl::Color outlineColor);
    private:
        sdl::Font* font;
        str path;
        int outlineSize;
        int size;

        void reloadFont();
	};

    // Update the font size and reload the font with the new size
    FFont& FFont::setOutlineSize(int size)
    {
        this->outlineSize = size;
        reloadFont();
        return *this;
    }

    // Update the font size and reload the font with the new size
    FFont& FFont::setSize(int size)
    {
        this->size = size;
        reloadFont();
        return *this;
    }

    // Create a texture snapshot of the text outline rendered with this font in the given color. Text must NOT be empty
    FFontRender FFont::makeOutline(strv text, uint32 w, sdl::Color color)
    {
        sdl::fontOutlineSet(font, outlineSize);
        sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), color, w);
        sdl::Texture* outlineTex = sdl::textureCreateFromSurface(outlineSurf);
        sdl::surfaceFree(outlineSurf);
        sdl::fontOutlineSet(font, 0);
        return { outlineTex, outlineSurf->w, outlineSurf->h };
    }

    // Create a texture snapshot of the text rendered with this font in the given color. Text must NOT be empty
    FFontRender FFont::makeText(strv text, uint32 w, sdl::Color color)
    {
        sdl::Surface* textSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), color, w);
        sdl::Texture* textTex = sdl::textureCreateFromSurface(textSurf);
        sdl::surfaceFree(textSurf);
        return { textTex, textSurf->w, textSurf->h };
    }

    /* Close the font */
    void FFont::dispose()
    {
        sdl::fontClose(font);
        font = nullptr;
    }

    // TODO return the textures created instead to be cached in a textinfo object
    /* Draw the font at the given x/y coordinates. */
    void FFont::draw(strv text, float x, float y, uint32 w = 0, sdl::Color color = sdl::WHITE, sdl::Color outlineColor = sdl::BLACK)
    {
        if (!text.empty()) {
            // Render outline
            sdl::fontOutlineSet(font, outlineSize);
            sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), outlineColor, w);
            sdl::Texture* outlineTex = sdl::textureCreateFromSurface(outlineSurf);
            sdl::RectF outlineRect = { x - outlineSize, y - outlineSize, outlineSurf->w, outlineSurf->h };
            sdl::renderCopy(outlineTex, nullptr, &outlineRect);
            sdl::surfaceFree(outlineSurf);
            sdl::textureDestroy(outlineTex);

            // Render the text
            sdl::fontOutlineSet(font, 0);
            sdl::Surface* textSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), color, w);
            sdl::Texture* textTex = sdl::textureCreateFromSurface(textSurf);
            sdl::RectF textRect = { x, y, textSurf->w, textSurf->h };
            sdl::renderCopy(textTex, nullptr, &textRect);
            sdl::surfaceFree(textSurf);
            sdl::textureDestroy(textTex);
        }
    }

    /* Refreshes the font to match its size */
    void FFont::reloadFont()
    {
        font = sdl::fontOpen(path.c_str(), size);
        if (font == nullptr) {
            sdl::logError("Failed to load font %s: %s", path.c_str(), sdl::getError());
            font = sdl::fontOpen(FONT_REGULAR.c_str(), size);
        }
        if (font == nullptr) {
            sdl::logError("RIP even the default font failed us %s", sdl::getError());
        }
    }
}