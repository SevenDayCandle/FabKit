export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import sdl;

export namespace fbc {
    const str FONT_REGULAR = "Resources/Fonts/Rubik-Regular.ttf";

    export struct FFontRender {
        sdl::Texture* texture;
        float w;
        float h;
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
        FFontRender makeTexture(strv text, uint32 w, sdl::Color color, sdl::Color outlineColor);
        void dispose();
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

    // Create a texture snapshot of the text rendered with this font in the given colors. Text must NOT be empty
    FFontRender FFont::makeTexture(strv text, uint32 w, sdl::Color color = sdl::WHITE, sdl::Color outlineColor = sdl::BLACK)
    {
        sdl::fontOutlineSet(font, outlineSize);
        sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), outlineColor, w);
        sdl::fontOutlineSet(font, 0);

        sdl::Surface* textSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), color, w);
        sdl::RectI targetRect = { outlineSize, outlineSize, textSurf->w, textSurf->h };
        sdl::surfaceBlit(textSurf, nullptr, outlineSurf, &targetRect);

        sdl::Texture* outlineTex = sdl::textureCreateFromSurface(outlineSurf);
        FFontRender f = { outlineTex, outlineSurf->w, outlineSurf->h };
        sdl::surfaceDestroy(outlineSurf);
        return f;
    }

    /* Close the font */
    void FFont::dispose()
    {
        sdl::fontClose(font);
        font = nullptr;
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