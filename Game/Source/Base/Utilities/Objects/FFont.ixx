export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import sdl;
import std;

export namespace fbc {
	export class FFont {
    public:
        FFont(strv path, int size = 12, int outlineSize = 4): size(size), outlineSize(outlineSize) {
            font = sdl::fontOpen(path.data(), size);
        }
        FFont(const FFont&) = delete;
        ~FFont() {
            // Unload font when destroyed
            sdl::fontClose(font);
        }

        sdl::Font* font;
        int outlineSize;
        int size;

        void draw(strv text, float x, float y, sdl::Color color, sdl::Color outlineColor);
	};


    void FFont::draw(strv text, float x, float y, sdl::Color color = sdl::WHITE, sdl::Color outlineColor = sdl::BLACK)
    {
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