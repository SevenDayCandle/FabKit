export module fbc.FTexture;

import fbc.FUtil;
import fbc.IDrawable;
import fbc.ILoadable;
import sdl;
import std;

export namespace fbc {
	export class FTexture : public IDrawable {
    public:
        FTexture(strv path) : path(path) {}
        FTexture(const FTexture&) = delete;
        ~FTexture() override {
            // Unload texture when destroyed
            if (texture && sdl::sdlEnabled()) {
                sdl::textureDestroy(texture);
                texture = nullptr;
            }
        }

        inline const sdl::RectF* getBaseRec() const override { return &dim; }
        inline float getHeight() const override { return dim.h; }
        inline float getWidth() const override { return dim.w; }

        void dispose() override;
        void drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip) override;
        void reload() override;
        void setDrawBlend(const sdl::BlendMode bl) override;
        void setDrawColor(const sdl::Color& tint) override;
    private:
        str path;
        sdl::RectF dim;
        sdl::Texture* texture;
        sdl::PixelFormatEnum format;
        int access;
	};

    void FTexture::dispose()
    {
        sdl::textureDestroy(texture);
        texture = nullptr;
    }

    void FTexture::drawBase(const sdl::RectF* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, sdl::FlipMode flip)
    {
        sdl::renderCopyEx(texture, sourceRec, destRec, rotation, &origin, flip);
    }

    void FTexture::reload()
    {
        if (texture) {
            sdl::textureDestroy(texture);
        }
        texture = sdl::textureLoad(path.data());
        if (texture == nullptr) {
            sdl::logError("Failed to load texture %s: %s", path, sdl::getError());
        }
        int w, h;
        sdl::textureQuery(texture, &format, &access, &w, &h);
        dim.w = w;
        dim.h = h;
    }

    void FTexture::setDrawBlend(const sdl::BlendMode bl)
    {
        sdl::textureSetBlendMode(texture, bl);
    }

    void FTexture::setDrawColor(const sdl::Color& tint)
    {
        sdl::textureSetColorMod(texture, tint.r, tint.g, tint.b);
        sdl::textureSetAlphaMod(texture, tint.a);
    }
}
