export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import raylib;
import std;

export namespace fbc {
	export class FFont : public raylib::Font {
    public:
        FFont(int baseSize,int glyphCount,int glyphPadding, const raylib::Texture& texture, raylib::Rectangle* recs = nullptr, raylib::GlyphInfo* glyphs = nullptr)
            : raylib::Font{ baseSize, glyphCount, glyphPadding, texture, recs, glyphs } {
        }
        /* Move constructor moves the other texture's data to this one */
        FFont(Font&& other) {
            baseSize = other.baseSize;
            glyphCount = other.glyphCount;
            glyphPadding = other.glyphPadding;
            texture = other.texture;
            recs = other.recs;
            glyphs = other.glyphs;

            other.baseSize = 0;
            other.glyphCount = 0;
            other.glyphPadding = 0;
            other.texture = {};
            other.recs = nullptr;
            other.glyphs = nullptr;
        }
        /**
         * Explicitly forbid copy constructor.
         */
        FFont(const FFont&) = delete;

        /**
		 * On destruction, unload the font.
		 */
        ~FFont() {
            raylib::unloadFont(*this);
        }

        // Write the given text
        void draw(const str& text, const raylib::Vector2& position, float fontSize, float spacing, const raylib::Color& tint = raylib::White) const {
            raylib::drawTextEx(*this, text.c_str(), position, fontSize, spacing, tint);
        }

        void draw(const str& text, float posX, float posY, float fontSize, float spacing, const raylib::Color& tint = raylib::White) const {
            raylib::drawTextEx(*this, text.c_str(),
                { posX, posY },
                fontSize, spacing, tint);
        }

        void draw(const str& text, const raylib::Vector2& position, const raylib::Vector2& origin, float rotation, float fontSize, float spacing, const raylib::Color& tint = raylib::White) const {
            raylib::drawTextPro(*this, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
        }

        void draw(int codepoint, const raylib::Vector2& position, float fontSize, raylib::Color tint = raylib::White) const {
            raylib::drawTextCodepoint(*this, codepoint, position, fontSize, tint);
        }

        void draw(const int* codepoints,int count, const raylib::Vector2& position,float fontSize, float spacing, const raylib::Color& tint = raylib::White) const {
            raylib::drawTextCodepoints(*this,
                codepoints, count,
                position, fontSize,
                spacing, tint);
        }

        /** Wrapper function around raylib::loadFont to get an FFont instead of a Font **/
        static uptr<FFont> loadFont(const str& path) {
            Font f = raylib::loadFont(path.c_str());
            return std::make_unique<FFont>(std::move(f));
        }
	};
}