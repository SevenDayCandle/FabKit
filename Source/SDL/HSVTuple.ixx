export module sdl.HSVTuple;

import sdl.SDLBase;
import std;

namespace sdl {
	export struct HSVTuple {
		float h, s, v;

		inline static HSVTuple toHSV(const Color& color) { return toHSV(color.r, color.g, color.b); }
        inline static void fromHSV(HSVTuple& tuple, Color& color) { fromHSV(tuple, color.r, color.g, color.b); }

        static Color fromHSV(HSVTuple& tuple, float a = 1);
		static HSVTuple toHSV(float r, float g, float b);
        static void fromHSV(HSVTuple& tuple, float& r, float& g, float& b);
		static void toHSV(HSVTuple& tuple, float r, float g, float b);
	};

    // Generate a new Color from a HSV tuple
    Color HSVTuple::fromHSV(HSVTuple& tuple, float a) {
        Color color = { 0, 0, 0, a };
        fromHSV(tuple, color);
        return color;
    }

    // Generate a new HSVTuple from the given RGB values
    HSVTuple HSVTuple::toHSV(float r, float g, float b) {
        HSVTuple tuple = {};
        toHSV(tuple, r, g, b);
        return tuple;
    }

    /* Assign RGB values from a HSVTuple's values
    *  Adapted from https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
       Multiply resulting hue by 6 because it was mapped to the range 0, 1 */
    void HSVTuple::fromHSV(HSVTuple& tuple, float& r, float& g, float& b) {
        float h = (tuple.h < 0 ? tuple.h + 1 : tuple.h > 1 ? tuple.h - 1 : tuple.h) * 6;  // Scale hue to the [0, 6] range
        float c = tuple.v * tuple.s;  // Chroma
        float m = tuple.v - c;        // Match value for RGB conversion
        float x = c * (1.0f - std::abs(std::fmod(h, 2.0f) - 1.0f));  // Calculate intermediate value
        int i = std::floor(h);  // Determine the sector of the color wheel

        switch (i % 6) {
        case 0:
            r = c + m;
            g = x + m;
            b = m;
            break;
        case 1:
            r = x + m;
            g = c + m;
            b = m;
            break;
        case 2:
            r = m;
            g = c + m;
            b = x + m;
            break;
        case 3:
            r = m;
            g = x + m;
            b = c + m;
            break;
        case 4:
            r = x + m;
            g = m;
            b = c + m;
            break;
        default:
            r = c + m;
            g = m;
            b = x + m;
            break;
        }
    }

    /* Updates a HSVTuple from the given RGB values
       Adapted from https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
       Divide resulting hue by 6 because we want to map it to the range 0, 1 */
	void HSVTuple::toHSV(HSVTuple& tuple, float r, float g, float b) {
        float cmax = std::max(r, std::max(g, b));
        float cmin = std::min(r, std::min(g, b));
        float diff = cmax - cmin;

        if (diff > 0.0f) {
            if (cmax == r) {
                tuple.h = ((g - b) / diff) / 6;
            }
            else if (cmax == g) {
                tuple.h = (2 + (b - r) / diff) / 6;
            }
            else {
                tuple.h = (4 + (r - g) / diff) / 6;
            }
            if (tuple.h < 0.0f) {
                tuple.h += 1.0f;
            }
        }
        else {
            tuple.h = 0;
        }

        tuple.s = (cmax == 0.0f) ? 0.0f : diff / cmax;
        tuple.v = cmax;
	}
}