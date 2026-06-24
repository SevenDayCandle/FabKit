module;

#include "SDL3/SDL.h"
#include "SDL3_shadercross/SDL_shadercross.h"

export module sdl.SDLHelpers;

import sdl.IKeyInputListener;
import std;

/* Operators */
export bool operator==(const SDL_FColor& lhs, const SDL_FColor& rhs) { return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a; }
export bool operator!=(const SDL_FColor& lhs, const SDL_FColor& rhs) { return !(lhs == rhs); }

namespace sdl {
	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_FColor;
	export using Point = ::SDL_FPoint;
	export using PointI = ::SDL_Point;
	export using RectF = ::SDL_FRect;
	export using RectI = ::SDL_Rect;
	export using Surface = ::SDL_Surface;
	export using Window = ::SDL_Window;
	export using ::Sint32;
	export using ::Sint64;
	export using ::Sint8;
	export using ::Uint32;
	export using ::Uint64;
	export using ::Uint8;

	export enum RenderMode {
		NORMAL,
		OVERLAY,
		GRAYSCALE
	};

	export struct Matrix4x4 {
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
	};

	export struct TexCoord {
		float x1, x2;
		float y1, y2;
		float w1, w2;
		float h1, h2;
	};

	// Fields need to be ordered by decreasing size, to ensure that the values align with required offsets for float4 and float2 data types in the shader
	export struct alignas(16) TexProps {
		Matrix4x4 transform;
		Color color;
		TexCoord coord;
		float texInd;
	};

	/* Color constants. RGB can be higher than 1 to make the image brighter */
	export constexpr Color COLOR_BLACK = {0, 0, 0, 1};
	export constexpr Color COLOR_BLACK_SHADOW = {0, 0, 0, 0.4f};
	export constexpr Color COLOR_GOLD = {1.0, 0.843, 0, 1};
	export constexpr Color COLOR_GRAY = {0.5f, 0.5f, 0.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_BLUE = {0.5f, 0.66f, 1.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_BLUE_LIGHT = {0.8f, 0.96f, 1.7f, 1};
	export constexpr Color COLOR_HIGHLIGHT_GREEN = {0.66f, 1.5f, 0.5f, 1};
	export constexpr Color COLOR_HIGHLIGHT_GREEN_LIGHT = {0.96f, 1.7f, 0.8f, 1};
	export constexpr Color COLOR_HIGHLIGHT_RED = {1.5f, 0.5f, 0.6f, 1};
	export constexpr Color COLOR_HIGHLIGHT_RED_LIGHT = {1.7f, 0.8f, 0.9f, 1};
	export constexpr Color COLOR_LIME = {0.6f, 1.5f, 0.84f, 1};
	export constexpr Color COLOR_SKY = {0.6f, 1.1, 1.5f, 1};
	export constexpr Color COLOR_STANDARD = {1, 1, 1, 1};
	export constexpr Color COLOR_WHITE = {2, 2, 2, 1};

	/* Scan constants (used for hotkeys) */
	export constexpr SDL_Scancode SCAN_BACKSPACE = SDL_SCANCODE_BACKSPACE;
	export constexpr SDL_Scancode SCAN_DOWN = SDL_SCANCODE_DOWN;
	export constexpr SDL_Scancode SCAN_ENTER = SDL_SCANCODE_KP_ENTER;
	export constexpr SDL_Scancode SCAN_ESC = SDL_SCANCODE_ESCAPE;
	export constexpr SDL_Scancode SCAN_LEFT = SDL_SCANCODE_LEFT;
	export constexpr SDL_Scancode SCAN_RETURN = SDL_SCANCODE_RETURN;
	export constexpr SDL_Scancode SCAN_RIGHT = SDL_SCANCODE_RIGHT;
	export constexpr SDL_Scancode SCAN_UP = SDL_SCANCODE_UP;

	/* Shader Stage */
	export constexpr SDL_ShaderCross_ShaderStage STAGE_FRAGMENT = SDL_SHADERCROSS_SHADERSTAGE_FRAGMENT;
	export constexpr SDL_ShaderCross_ShaderStage STAGE_VERTEX = SDL_SHADERCROSS_SHADERSTAGE_VERTEX;

	/* Key constants (used for input listeners) */
	export constexpr Sint32 KEY_BACKSPACE = SDLK_BACKSPACE;
	export constexpr Sint32 KEY_DOWN = SDLK_DOWN;
	export constexpr Sint32 KEY_ENTER = SDLK_KP_ENTER;
	export constexpr Sint32 KEY_ESC = SDLK_ESCAPE;
	export constexpr Sint32 KEY_LEFT = SDLK_LEFT;
	export constexpr Sint32 KEY_RETURN = SDLK_RETURN;
	export constexpr Sint32 KEY_RIGHT = SDLK_RIGHT;
	export constexpr Sint32 KEY_UP = SDLK_UP;

	/* Other constants */
	export constexpr Uint64 NANOS_PER_SECOND = 1000000000ULL;

	/* Misc functions */
	export inline const char* __cdecl getError() { return SDL_GetError(); }
	export inline constexpr float rads(float deg) { return deg * std::numbers::pi_v<float> / 180; }

	export inline SDL_Color toTextColor(const Color& c) {
		return {
			static_cast<Uint8>(255 * c.r),
			static_cast<Uint8>(255 * c.g),
			static_cast<Uint8>(255 * c.b),
			static_cast<Uint8>(255 * c.a),
		};
	}

	export inline void free(void* code) { SDL_free(code); }
	export template <typename... Args> inline void log(SDL_LogPriority priority, const char* message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message, args...); }
	export template <typename... Args> inline void log(SDL_LogPriority priority, std::string_view message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.data(), args...); }
	export template <typename... Args> inline void logCritical(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_CRITICAL, message, args...); }
	export template <typename... Args> inline void logCritical(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_CRITICAL, message, args...); }
	export template <typename... Args> inline void logInfo(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> inline void logInfo(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_INFO, message, args...); }
	export template <typename... Args> inline void logError(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
	export template <typename... Args> inline void logError(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
}
