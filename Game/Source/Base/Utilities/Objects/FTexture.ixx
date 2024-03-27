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
            sdl::textureQuery(texture, &format, &access, &dim.w, &dim.h);
        }
        FTexture(const FTexture&) = delete;
        ~FTexture() {
            // Unload texture when destroyed
            sdl::textureDestroy(texture);
        }

        sdl::RectI dim;
        sdl::Texture* texture;
        std::uint32_t format;
        int access;
        int width;
        int height;

        void draw(const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override {
            sdl::renderSetDrawColor(tint);
            sdl::renderCopyEx(texture, &dim, destRec, rotation, &origin, flip);
        }

        void draw(const sdl::RectI* sourceRec, const sdl::RectF* destRec, const sdl::Point& origin = { 0, 0 }, float rotation = 0, const sdl::Color& tint = sdl::WHITE, sdl::RendererFlip flip = SDL_FLIP_NONE) override {
            sdl::renderSetDrawColor(tint);
            sdl::renderCopyEx(texture, sourceRec, destRec, rotation, &origin, flip);
        }

        float getHeight() {
            return dim.h;
        }

        float getWidth() {
            return dim.w;
        }
	};
}