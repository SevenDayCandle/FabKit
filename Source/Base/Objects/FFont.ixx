export module fab.FFont;

import fab.FTexture;
import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

namespace fab {
	export class FFont : public ILoadable {
    public:
        FFont(strv path, float scalar, int size, int outlineSize = 0, int shadowSize = 0): path(path), globalScale(scalar), size(size), outlineSize(outlineSize), shadowSize(shadowSize) {
            FFont::reload();
        }
        FFont(const FFont&) = delete;
        virtual ~FFont() override {
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
        FFont& setGlobalScale(float scale);
        FFont& setOutlineSize(int size);
        FFont& setShadowSize(int size);
        FFont& setSize(int size);
        int measureH(strv text) const;
        int measureW(strv text) const;
        pair<int, int> measureDim(strv text) const;
        sdl::Surface* makeSurface(strv text, uint32 w = 0, const sdl::Color& color = sdl::COLOR_STANDARD, const sdl::Color& outlineColor = sdl::COLOR_BLACK, const sdl::Color& shadowColor = sdl::COLOR_BLACK_SHADOW);
        void dispose();
        void reload() const override;
    private:
        mutable sdl::Font* font;
        float globalScale = 1;
        str path;
        int outlineSize;
        int shadowSize;
        int size;
	};

    // Get the x and y sizes of the given text written with this font
    pair<int, int> FFont::measureDim(strv text) const
    {
        pair<int, int> pair;
        sdl::fontSizeText(font, text.data(), &pair.first, &pair.second);
        return pair;
    }

    // Get the x size of the given text written with this font
    int FFont::measureH(strv text) const
    {
        int w, h;
        sdl::fontSizeText(font, text.data(), &w, &h);
        return h;
    }

    // Get the y size of the given text written with this font
    int FFont::measureW(strv text) const
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

    FFont& FFont::setGlobalScale(float scale) {
        this->globalScale = scale;
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

    // Create a texture snapshot of the text rendered with this font in the given colors. Returns nullptr if the text was empty
    sdl::Surface* FFont::makeSurface(strv text, uint32 w, const sdl::Color& color, const sdl::Color& outlineColor, const sdl::Color& shadowColor)
    {
        const char* texDat = text.data();
        sdl::Surface* targetSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, sdl::toTextColor(color), w);

        if (targetSurf) {
            if (outlineSize > 0) {
                int res = globalScale * (outlineSize);
                sdl::fontOutlineSet(font, res);
                sdl::Surface* outlineSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, sdl::toTextColor(outlineColor), w);
                sdl::fontOutlineSet(font, 0);
                sdl::RectI targetRect = { res, res, targetSurf->w, targetSurf->h };
                sdl::surfaceBlitScaled(targetSurf, nullptr, outlineSurf, &targetRect, sdl::ScaleMode::SDL_SCALEMODE_LINEAR);
                sdl::surfaceDestroy(targetSurf);
                targetSurf = outlineSurf;
            }

            if (shadowSize > 0) {
                int res = globalScale * (shadowSize);
                sdl::Surface* shadowSurf = sdl::textRenderUTF8BlendedWrapped(font, texDat, sdl::toTextColor(shadowColor), w);
                sdl::Surface* newTargetSurf = sdl::surfaceCreate(targetSurf->w + res, targetSurf->h + res, targetSurf->format);
                sdl::RectI shadowRect = { res, res, shadowSurf->w, shadowSurf->h };
                sdl::RectI clipRect;
                sdl::surfaceGetClipRect(targetSurf, &clipRect);
                sdl::surfaceBlitScaled(shadowSurf, nullptr, newTargetSurf, &shadowRect, sdl::ScaleMode::SDL_SCALEMODE_LINEAR);
                sdl::surfaceBlitScaled(targetSurf, nullptr, newTargetSurf, &clipRect, sdl::ScaleMode::SDL_SCALEMODE_LINEAR);
                sdl::surfaceDestroy(targetSurf);
                sdl::surfaceDestroy(shadowSurf);
                targetSurf = newTargetSurf;
            }
        }

        return targetSurf;
    }

    /* Close the font */
    void FFont::dispose()
    {
        sdl::fontClose(font);
        font = nullptr;
    }

    /* Refreshes the font to match its size */
    void FFont::reload() const
    {
        int res = globalScale * (size);
        font = sdl::fontOpen(path.c_str(), res);
        if (font == nullptr) {
            sdl::logError("Failed to load font %s: %s", path.c_str(), sdl::getError());
        }
    }
}