export module fbc.FFont;

import fbc.CoreConfig;
import fbc.FTexture;
import fbc.FUtil;
import fbc.ILoadable;
import sdl;

namespace fbc {
	export class FFont : public ILoadable {
    public:
        FFont(strv path, int size, int outlineSize = 0, int shadowSize = 0): path(path), size(size), outlineSize(outlineSize), shadowSize(shadowSize) {
            reload();
        }
        FFont(const FFont&) = delete;
        virtual ~FFont() {
            // Unload font when destroyed
            if (font) {
                sdl::fontClose(font);
                font = nullptr;
            }
        }

        inline int getOutlineSize() const { return outlineSize; }
        inline int getShadowSize() const { return outlineSize; }
        inline int getSize() const { return size; }

        FFont& setAllSizes(int size, int outlineSize, int shadowSize);
        FFont& setOutlineSize(int size);
        FFont& setShadowSize(int size);
        FFont& setSize(int size);
        int measureH(strv text);
        int measureW(strv text);
        pair<int, int> measureDim(strv text);
        sdl::FontRender makeTexture(strv text, uint32 w, float x, float y, sdl::Color color, sdl::Color outlineColor, sdl::Color shadowColor);
        void dispose();
        void reload();
    private:
        sdl::Font* font;
        str path;
        int outlineSize;
        int shadowSize;
        int size;
	};

    // Get the x and y sizes of the given text written with this font
    pair<int, int> FFont::measureDim(strv text)
    {
        pair<int, int> pair;
        sdl::fontSizeText(font, text.data(), &pair.first, &pair.second);
        return pair;
    }

    // Get the x size of the given text written with this font
    int FFont::measureH(strv text)
    {
        int w, h;
        sdl::fontSizeText(font, text.data(), &w, &h);
        return h;
    }

    // Get the y size of the given text written with this font
    int FFont::measureW(strv text)
    {
        int w, h;
        sdl::fontSizeText(font, text.data(), &w, &h);
        return w;
    }

    // Update all sizes and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
    FFont& FFont::setAllSizes(int size, int outlineSize, int shadowSize)
    {
        this->size = size;
        this->outlineSize = outlineSize;
        this->shadowSize = shadowSize;
        reload();
        return *this;
    }

    // Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
    FFont& FFont::setOutlineSize(int size)
    {
        this->outlineSize = size;
        return *this;
    }

    // Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
    FFont& FFont::setShadowSize(int size)
    {
        this->shadowSize = size;
        return *this;
    }

    // Update the font size and reload the font with the new size. Note that sizes will be scaled by fontScale and should not be multiplied by it beforehand.
    FFont& FFont::setSize(int size)
    {
        this->size = size;
        reload();
        return *this;
    }

    // Create a texture snapshot of the text rendered with this font in the given colors. Text must NOT be empty
    sdl::FontRender FFont::makeTexture(strv text, uint32 w = 0, float x = 0, float y = 0, sdl::Color color = sdl::COLOR_WHITE, sdl::Color outlineColor = sdl::COLOR_BLACK, sdl::Color shadowColor = sdl::COLOR_BLACK_SHADOW)
    {
        const char* texDat = text.data();
        sdl::Surface* targetSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, color, w);

        if (outlineSize > 0) {
            int res = cfg.fontScale(outlineSize);
            sdl::fontOutlineSet(font, res);
            sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, outlineColor, w);
            sdl::fontOutlineSet(font, 0);
            sdl::RectI targetRect = { res, res, targetSurf->w, targetSurf->h };
            sdl::surfaceBlitScaled(targetSurf, nullptr, outlineSurf, &targetRect, sdl::ScaleMode::SDL_SCALEMODE_BEST);
            sdl::surfaceDestroy(targetSurf);
            targetSurf = outlineSurf;
        }

        if (shadowSize > 0) {
            int res = cfg.fontScale(shadowSize);
            sdl::Surface* shadowSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, shadowColor, w);
            sdl::Surface* newTargetSurf = sdl::surfaceCreate(targetSurf->w + res, targetSurf->h + res, targetSurf->format->format);
            sdl::RectI shadowRect = { res, res, shadowSurf->w, shadowSurf->h };
            sdl::surfaceBlitScaled(shadowSurf, nullptr, newTargetSurf, &shadowRect, sdl::ScaleMode::SDL_SCALEMODE_BEST);
            sdl::surfaceBlitScaled(targetSurf, nullptr, newTargetSurf, &targetSurf->clip_rect, sdl::ScaleMode::SDL_SCALEMODE_BEST);
            sdl::surfaceDestroy(targetSurf);
            sdl::surfaceDestroy(shadowSurf);
            targetSurf = newTargetSurf;
        }

        sdl::Texture* tex = sdl::textureCreateFromSurface(targetSurf);
        sdl::FontRender f = {  x, y, targetSurf->w, targetSurf->h , tex };
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
    void FFont::reload()
    {
        int res = cfg.fontScale(size);
        font = sdl::fontOpen(path.c_str(), res);
        if (font == nullptr) {
            sdl::logError("Failed to load font %s: %s", path.c_str(), sdl::getError());
            font = sdl::fontOpen(FONT_REGULAR.data(), res);
        }
        if (font == nullptr) {
            sdl::logError("RIP even the default font failed us %s", sdl::getError());
        }
    }
}