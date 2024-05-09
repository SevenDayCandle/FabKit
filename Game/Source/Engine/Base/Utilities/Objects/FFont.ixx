export module fbc.FFont;

import fbc.FTexture;
import fbc.futil;
import sdl;

export namespace fbc {
    const str FONT_BOLD = "Resources/Fonts/NotoSans-Bold.ttf";
    const str FONT_REGULAR = "Resources/Fonts/NotoSans-Regular.ttf";

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

        inline int getOutlineSize() const { return outlineSize; }
        inline int getShadowSize() const { return outlineSize; }
        inline int getSize() const { return size; }
        pair<int, int> measureDim(strv text);
        int measureH(strv text);
        int measureW(strv text);

        FFont& setOutlineSize(int size);
        FFont& setSize(int size);
        sdl::FontRender makeTexture(strv text, uint32 w, sdl::Color color, sdl::Color outlineColor, sdl::Color shadowColor);
        void dispose();
    private:
        sdl::Font* font;
        str path;
        int outlineSize;
        int shadowSize;
        int size;

        void reloadFont();
	};

    pair<int, int> FFont::measureDim(strv text)
    {
        pair<int, int> pair;
        sdl::fontSizeText(font, text.data(), &pair.first, &pair.second);
        return pair;
    }

    int FFont::measureH(strv text)
    {
        int w, h;
        sdl::fontSizeText(font, text.data(), &w, &h);
        return h;
    }

    int FFont::measureW(strv text)
    {
        int w, h;
        sdl::fontSizeText(font, text.data(), &w, &h);
        return w;
    }

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
    sdl::FontRender FFont::makeTexture(strv text, uint32 w = 0, sdl::Color color = sdl::COLOR_WHITE, sdl::Color outlineColor = sdl::COLOR_BLACK, sdl::Color shadowColor = sdl::COLOR_BLACK_SHADOW)
    {
        const char* texDat = text.data();
        sdl::Surface* targetSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, color, w);

        if (outlineSize > 0) {
            sdl::fontOutlineSet(font, outlineSize);
            sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, outlineColor, w);
            sdl::fontOutlineSet(font, 0);
            sdl::RectI targetRect = { outlineSize, outlineSize, targetSurf->w, targetSurf->h };
            sdl::surfaceBlitScaled(targetSurf, nullptr, outlineSurf, &targetRect, sdl::ScaleMode::SDL_SCALEMODE_BEST);
            sdl::Surface* origSurf = targetSurf;
            targetSurf = outlineSurf;
            sdl::surfaceDestroy(origSurf);
        }

        if (shadowSize > 0) {
            sdl::Surface* shadowSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, shadowColor, w);
            sdl::RectI targetRect = { -shadowSize, -shadowSize, targetSurf->w, targetSurf->h };
            sdl::surfaceBlit(targetSurf, nullptr, shadowSurf, &targetRect);
            sdl::Surface* origSurf = targetSurf;
            targetSurf = shadowSurf;
            sdl::surfaceDestroy(origSurf);
        }

        sdl::Texture* tex = sdl::textureCreateFromSurface(targetSurf);
        sdl::FontRender f = { tex, targetSurf->w, targetSurf->h };
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