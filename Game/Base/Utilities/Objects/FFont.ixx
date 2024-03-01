export module fbc.ffont;

import fbc.ftexture;
import fbc.futil;
import raylib;

export namespace fbc {
	export class FFont : public raylib::Font {
    public:
        FFont(int baseSize,int glyphCount,int glyphPadding, fbc::FTexture texture, raylib::Rectangle* recs = nullptr, raylib::GlyphInfo* glyphs = nullptr)
            : raylib::Font{ baseSize, glyphCount, glyphPadding, texture, recs, glyphs } {
        }
        ~FFont() {
            raylib::unloadFont(*this);
        }

        // Write the given text
        void draw(const str& text, raylib::Vector2 position, float fontSize, float spacing, raylib::Color tint = raylib::White) const {
            raylib::drawTextEx(*this, text.c_str(), position, fontSize, spacing, tint);
        }

        void draw(const str& text, float posX, float posY, float fontSize, float spacing, raylib::Color tint = raylib::White) const {
            raylib::drawTextEx(*this, text.c_str(),
                { posX, posY },
                fontSize, spacing, tint);
        }

        void draw(const str& text, raylib::Vector2 position, raylib::Vector2 origin, float rotation, float fontSize, float spacing, raylib::Color tint = raylib::White) const {
            raylib::drawTextPro(*this, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
        }

        void draw(int codepoint, raylib::Vector2 position, float fontSize, raylib::Color tint = raylib::White) const {
            raylib::drawTextCodepoint(*this, codepoint, position, fontSize, tint);
        }

        void draw(const int* codepoints,int count, raylib::Vector2 position,float fontSize, float spacing, raylib::Color tint = raylib::White) const {
            raylib::drawTextCodepoints(*this,
                codepoints, count,
                position, fontSize,
                spacing, tint);
        }
	};
}