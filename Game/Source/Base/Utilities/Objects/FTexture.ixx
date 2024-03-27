export module fbc.ftexture;

import fbc.futil;
import fbc.iDrawable;
import sdl;
import std;

export namespace fbc {
	export class FTexture : public IDrawable {
    public:
        FTexture(strv path) {
            texture = sdl::textureLoad(path.data());
            if (texture == nullptr) {
                sdl::logError("Failed to load texture %s: %s", path.data(), sdl::getError());
            }
            sdl::textureQuery(texture, &format, &access, &dim.w, &dim.h);
        }
        FTexture(const FTexture&) = delete;
        ~FTexture() {
            // Unload texture when destroyed
            if (texture) {
                sdl::textureDestroy(texture);
                texture = nullptr;
            }
        }

        sdl::RectI dim;
        sdl::Texture* texture;
        std::uint32_t format;
        int access;

        inline float getHeight() { return dim.h; }
        inline float getWidth() { return dim.w; }

        void dispose();
        void draw(const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override;
        void draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override;
	};

    void FTexture::dispose()
    {
        sdl::textureDestroy(texture);
        texture = nullptr;
    }

    void FTexture::draw(const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) {
        sdl::renderSetDrawColor(tint);
        sdl::renderCopyEx(texture, &dim, destRec, rotation, &origin, flip);
    }

    void FTexture::draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin, float rotation, const sdl::Color& tint, sdl::RendererFlip flip) {
        sdl::renderSetDrawColor(tint);
        sdl::renderCopyEx(texture, sourceRec, destRec, rotation, &origin, flip);
    }
}