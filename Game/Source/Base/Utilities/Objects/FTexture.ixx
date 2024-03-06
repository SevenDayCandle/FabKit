export module fbc.ftexture;

import fbc.futil;
import raylib;
import std;

export namespace fbc {
	export class FTexture : public raylib::Texture {
    public:
        /* Move constructor moves the other texture's data to this one */
        FTexture(Texture&& other) {
            this->id = other.id;
            this->width = other.width;
            this->height = other.height;
            this->mipmaps = other.mipmaps;
            this->format = other.format;

            other.id = 0;
            other.width = 0;
            other.height = 0;
            other.mipmaps = 0;
            other.format = 0;
        }
        /**
         * Explicitly forbid copy constructor and assignment.
         */
        FTexture(const FTexture&) = delete;
        FTexture& operator=(const FTexture&) = delete;

        /**
         * On destruction, unload the Texture.
         */
        ~FTexture() {
            raylib::unloadTexture(*this);
        }

        /**
         * Generate GPU mipmaps for a texture
         */
        FTexture& genMipmaps() {
            raylib::genTextureMipmaps(this);
            return *this;
        }

        /**
         * Get pixel data from GPU texture and return an Image
         */
        raylib::Image getData() const {
            return raylib::loadImageFromTexture(*this);
        }

        operator raylib::Image() {
            return getData();
        }

        /**
         * Set texture scaling filter mode
         */
        FTexture& setFilter(int filterMode) {
            raylib::setTextureFilter(*this, filterMode);
            return *this;
        }

        /**
         * Update GPU texture with new data
         */
        FTexture& setPixels(const void* pixels) {
            raylib::updateTexture(*this, pixels);
            return *this;
        }

        /**
         * Set shader uniform value for texture (sampler2d)
         */
        FTexture& setShader(const raylib::Shader& shader, int locIndex) {
            raylib::setShaderValueTexture(shader, locIndex, *this);
            return *this;
        }

        /**
         * Set texture wrapping mode
         */
        FTexture& setWrap(int wrapMode) {
            raylib::setTextureWrap(*this, wrapMode);
            return *this;
        }

        /**
         * Draw a Texture2D
         *
         * @see ::DrawTexture()
         */
        void draw(int posX = 0, int posY = 0, const raylib::Color& tint = raylib::White) const {
            raylib::drawTexture(*this, posX, posY, tint);
        }

        /**
         * Draw a Texture2D with position defined as Vector2
         *
         * @see ::DrawTextureV()
         */
        void draw(const raylib::Vector2& position, const raylib::Color& tint = raylib::White) const {
            raylib::drawTextureV(*this, position, tint);
        }

        /**
         * Draw a Texture2D with extended parameters
         *
         * @see ::DrawTextureEx()
         */
        void draw(const raylib::Vector2& position, float rotation, float scale = 1.0f,
            raylib::Color tint = raylib::White) const {
            raylib::drawTextureEx(*this, position, rotation, scale, tint);
        }

        /**
         * Draw a part of a texture defined by a rectangle
         *
         * @see ::DrawTextureRec()
         */
        void draw(const raylib::Rectangle& sourceRec, const raylib::Vector2& position = { 0, 0 },
            raylib::Color tint = raylib::White) const {
            raylib::drawTextureRec(*this, sourceRec, position, tint);
        }

        /**
         * Draw a part of a texture defined by a rectangle with 'pro' parameters
         *
         * @see ::DrawTexturePro()
         */
        void draw(const raylib::Rectangle& sourceRec, const raylib::Rectangle& destRec, const raylib::Vector2& origin = { 0, 0 },
            float rotation = 0, raylib::Color tint = raylib::White) const {
            raylib::drawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
        }

        /** Wrapper function around raylib::loadTexture to get an FTexture instead of a Texture **/
        static sptr<FTexture> loadTexture(const str& fileName) {
            Texture tex = raylib::loadTexture(fileName.c_str());
            return std::make_shared<FTexture>(std::move(tex));
        }
	};
}