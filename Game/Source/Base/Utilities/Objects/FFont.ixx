export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import sdl;
import std;

export namespace fbc {
    const str FONT_REGULAR = "Resources/Fonts/Rubik-Regular.ttf";

	export class FFont {
    public:
        FFont(strv path, int size = 12, int outlineSize = 4): size(size), outlineSize(outlineSize) {
            font = sdl::fontOpen(path.data(), size);
            if (font == nullptr) {
                sdl::logError("Failed to load font %s: %s", path.data(), sdl::getError());
                font = sdl::fontOpen(FONT_REGULAR.c_str(), size);
            }
            if (font == nullptr) {
                sdl::logError("RIP %s", sdl::getError());
            }
        }
        FFont(const FFont&) = delete;
        ~FFont() {
            // Unload font when destroyed
            if (font) {
                sdl::fontClose(font);
                font = nullptr;
            }
        }

        sdl::Font* font;
        int outlineSize;
        int size;

        void dispose();
        void draw(strv text, float x, float y, sdl::Color color, sdl::Color outlineColor);
	};


    void FFont::dispose()
    {
        sdl::fontClose(font);
        font = nullptr;
    }

    void FFont::draw(strv text, float x, float y, sdl::Color color = sdl::WHITE, sdl::Color outlineColor = sdl::BLACK)
    {
        if (!text.empty()) {
            sdl::fontOutlineSet(font, outlineSize);
            sdl::Surface* outlineSurf = sdl::textRenderSolid(font, text.data(), outlineColor);
            sdl::Texture* outlineTex = sdl::textureCreateFromSurface(outlineSurf);
            sdl::RectF outlineRect = { x, y, outlineSurf->w, outlineSurf->h };
            sdl::renderCopy(outlineTex, nullptr, &outlineRect);
            sdl::surfaceFree(outlineSurf);
            sdl::textureDestroy(outlineTex);

            // Render the text on top
            sdl::fontOutlineSet(font, 0); // Reset outline to zero for main text
            sdl::Surface* textSurf = sdl::textRenderSolid(font, text.data(), color);
            sdl::Texture* textTex = sdl::textureCreateFromSurface(textSurf);
            sdl::RectF textRect = { x - outlineSize, y - outlineSize, textSurf->w, textSurf->h };
            sdl::renderCopy(textTex, nullptr, &textRect);
            sdl::surfaceFree(textSurf);
            sdl::textureDestroy(textTex);
        }
    }
}