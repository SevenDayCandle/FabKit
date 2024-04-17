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
        FFont(str path, int size, int outlineSize = 0, int shadowSize = 0): path(path), size(size), outlineSize(outlineSize), shadowSize(shadowSize) {
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
        inline int getShadowSize() { return outlineSize; }
        inline int getSize() { return size; }

        FFont& setOutlineSize(int size);
        FFont& setSize(int size);
        FFontRender makeTexture(strv text, uint32 w, sdl::Color color, sdl::Color outlineColor, sdl::Color shadowColor);
        void dispose();
    private:
        sdl::Font* font;
        str path;
        int outlineSize;
        int shadowSize;
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
    FFontRender FFont::makeTexture(strv text, uint32 w, sdl::Color color = sdl::WHITE, sdl::Color outlineColor = sdl::BLACK, sdl::Color shadowColor = sdl::BLACK_SHADOW)
    {
        sdl::Surface* targetSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), color, w);

        if (outlineSize > 0) {
            sdl::fontOutlineSet(font, outlineSize);
            sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), outlineColor, w);
            sdl::fontOutlineSet(font, 0);
            sdl::RectI targetRect = { outlineSize, outlineSize, targetSurf->w, targetSurf->h };
            sdl::surfaceBlit(targetSurf, nullptr, outlineSurf, &targetRect);
            sdl::Surface* origSurf = targetSurf;
            targetSurf = outlineSurf;
            sdl::surfaceDestroy(origSurf);
        }

        if (shadowSize > 0) {
            sdl::Surface* shadowSurf = sdl::textRenderUTF8BlendedWrapped(font, text.data(), shadowColor, w);
            sdl::RectI targetRect = { -shadowSize, -shadowSize, targetSurf->w, targetSurf->h };
            sdl::surfaceBlit(targetSurf, nullptr, shadowSurf, &targetRect);
            sdl::Surface* origSurf = targetSurf;
            targetSurf = shadowSurf;
            sdl::surfaceDestroy(origSurf);
        }

        sdl::Texture* tex = sdl::textureCreateFromSurface(targetSurf);
        FFontRender f = { tex, targetSurf->w, targetSurf->h };
        sdl::surfaceDestroy(targetSurf);
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