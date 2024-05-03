module;

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstring>

export module sdl;

import sdl.iKeyInputListener;
import std;

namespace sdl {
	const Uint8* key;
	const Uint8* pad;
	int mouse = -1;
	int mouseLast = -1;
	int mousePosX = 0;
	int mousePosY = 0;
	int numKeys;
	int numPads;
	IKeyInputListener* kListener;
	SDL_Event e;
	SDL_Gamepad* gamepad;
	SDL_Renderer* renderer;
	SDL_Window* window;
	Uint32 timeStart;
	Uint8* keyLast;
	Uint8* padLast;

	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_Color;
	export using FlipMode = ::SDL_FlipMode;
	export using Font = ::TTF_Font;
	export using GamepadButton = ::SDL_GamepadButton;
	export using PixelFormatEnum = ::SDL_PixelFormatEnum;
	export using Point = ::SDL_FPoint;
	export using PointI = ::SDL_Point;
	export using RectF = ::SDL_FRect;
	export using RectI = ::SDL_Rect;
	export using Surface = ::SDL_Surface;
	export using Texture = ::SDL_Texture;

	/* Color constants */
	export constexpr Color COLOR_BLACK = { 0, 0, 0, 255 };
	export constexpr Color COLOR_BLACK_SHADOW = { 0, 0, 0, 100 };
	export constexpr Color COLOR_GOLD = { 239, 200, 81, 255 };
	export constexpr Color COLOR_GRAY = { 127, 127, 127, 255 };
	export constexpr Color COLOR_LIME = { 76, 255, 57, 255 };
	export constexpr Color COLOR_WHITE = { 255, 255, 255, 255 };

	/* Key constants */
	export constexpr Sint32 KEY_BACKSPACE = SDLK_BACKSPACE;
	export constexpr Sint32 KEY_DOWN = SDLK_DOWN;
	export constexpr Sint32 KEY_ENTER = SDLK_KP_ENTER;
	export constexpr Sint32 KEY_ESC = SDLK_ESCAPE;
	export constexpr Sint32 KEY_LEFT = SDLK_UP;
	export constexpr Sint32 KEY_RIGHT = SDLK_UP;
	export constexpr Sint32 KEY_UP = SDLK_UP;

	/* Directory stuff */
	export char* dirBase() noexcept { return SDL_GetBasePath(); }
	export char* dirPref(const char* org, const char* app) { return SDL_GetPrefPath(org, app); }

	/* Font management functions */
	export int fontAscent(TTF_Font* font) { return TTF_FontAscent(font); }
	export void fontClose(TTF_Font* font) { TTF_CloseFont(font); }
	export int fontDescent(TTF_Font* font) { return TTF_FontDescent(font); }
	export int fontFaceIsFixedWidth(TTF_Font* font) { return TTF_FontFaceIsFixedWidth(font); }
	export long fontFaces(TTF_Font* font) { return TTF_FontFaces(font); }
	export int fontGlyphIsProvided(TTF_Font* font, Uint16 ch) { return TTF_GlyphIsProvided(font, ch); }
	export int fontGlyphMetrics(TTF_Font* font, Uint16 ch, int* minx, int* maxx, int* miny, int* maxy, int* advance) { return TTF_GlyphMetrics(font, ch, minx, maxx, miny, maxy, advance); }
	export int fontHeight(TTF_Font* font) { return TTF_FontHeight(font); }
	export int fontHintingGet(TTF_Font* font) { return TTF_GetFontHinting(font); }
	export void fontHintingSet(TTF_Font* font, int hinting) { TTF_SetFontHinting(font, hinting); }
	export int fontKerningGet(TTF_Font* font) { return TTF_GetFontKerning(font); }
	export void fontKerningSet(TTF_Font* font, int allowed) { TTF_SetFontKerning(font, allowed); }
	export int fontLineSkip(TTF_Font* font) { return TTF_FontLineSkip(font); }
	export TTF_Font* fontOpen(const char* file, int ptsize) { return TTF_OpenFont(file, ptsize); }
	export TTF_Font* fontOpenIndex(const char* file, int ptsize, long index) { return TTF_OpenFontIndex(file, ptsize, index); }
	export TTF_Font* fontOpenIndexIO(SDL_IOStream* src, int closeio, int ptsize, long index) { return TTF_OpenFontIndexIO(src, closeio, ptsize, index); }
	export TTF_Font* fontOpenIO(SDL_IOStream* src, int closeio, int ptsize) { return TTF_OpenFontIO(src, closeio, ptsize); }
	export int fontOutlineGet(TTF_Font* font) { return TTF_GetFontOutline(font); }
	export void fontOutlineSet(TTF_Font* font, int outline) { TTF_SetFontOutline(font, outline); }
	export int fontSizeText(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeText(font, text, w, h); }
	export int fontSizeUNICODE(TTF_Font* font, const Uint16* text, int* w, int* h) { return TTF_SizeUNICODE(font, text, w, h); }
	export int fontSizeUTF8(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeUTF8(font, text, w, h); }
	export int fontStyleIsSet(TTF_Font* font, int style) { return TTF_GetFontStyle(font) & style; }
	export void fontStyleSet(TTF_Font* font, int style) { TTF_SetFontStyle(font, style); }

	/* Gamepad functions */
	export bool gamepadHasJustPressed(int pressed) { return pad[pressed] && !padLast[pressed]; }

	/* Keyboard functions */
	export bool keyboardInputActive() {return kListener != nullptr;}
	export bool keyboardInputActive(IKeyInputListener* listener) { return kListener == listener; }
	export void keyboardInputStart(IKeyInputListener* listener) {
		if (!kListener) {
			kListener = listener;
			SDL_StartTextInput();
		}
	}
	export void keyboardInputStop() {
		kListener = nullptr;
		SDL_StopTextInput();
	}
	export void keyboardInputStopRequest(IKeyInputListener* listener) {
		if (kListener == listener) {
			kListener = nullptr;
			SDL_StopTextInput();
		}
	}
	export bool keyboardJustPressed(int pressed) { return key[pressed] && !keyLast[pressed]; }
	export bool keyboardJustPressedEnter() { return keyboardJustPressed(SDLK_KP_ENTER); }
	export bool keyboardJustPressedEsc() { return keyboardJustPressed(SDLK_ESCAPE); }
	export bool keyboardtPressed(int pressed) { return key[pressed]; }

	/* Mouse state functions */
	export int mouseGetX() noexcept { return mousePosX; }
	export int mouseGetY() noexcept { return mousePosY; }
	export bool mouseIsHovering(const RectF& rect) {
		int mx = sdl::mouseGetX();
		int my = sdl::mouseGetY();
		return mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h;
	}
	export bool mouseIsHovering(const RectI rect) {
		int mx = sdl::mouseGetX();
		int my = sdl::mouseGetY();
		return mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h;
	}
	export bool mouseIsLeftClicked() noexcept { return mouse == SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustClicked() noexcept { return mouse == SDL_BUTTON_LEFT && mouseLast != SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustReleased() noexcept { return mouse != SDL_BUTTON_LEFT && mouseLast == SDL_BUTTON_LEFT; }
	export bool mouseIsLeftReleased() noexcept { return mouse != SDL_BUTTON_LEFT; }
	export bool mouseIsRightClicked() noexcept { return mouse == SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustClicked() noexcept { return mouse == SDL_BUTTON_RIGHT && mouseLast != SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustReleased() noexcept { return mouse != SDL_BUTTON_RIGHT && mouseLast == SDL_BUTTON_RIGHT; }
	export bool mouseIsRightReleased() noexcept { return mouse != SDL_BUTTON_RIGHT; }

	/* Rendering functions */
	export void renderClear() { SDL_RenderClear(renderer); }
	export void renderCopy(Texture* texture, const RectF* srcrect, const RectF* dstrect) { SDL_RenderTexture(renderer, texture, srcrect, dstrect); }
	export void renderCopyEx(Texture* texture, const RectF* srcrect, const RectF* dstrect, const double angle, const Point* center, const SDL_FlipMode flip) { SDL_RenderTextureRotated(renderer, texture, srcrect, dstrect, angle, center, flip); }
	export void renderLine(float x1, float y1, float x2, float y2) { SDL_RenderLine(renderer, x1, y1, x2, y2); }
	export void renderLines(const Point* points, int count) { SDL_RenderLines(renderer, points, count); }
	export void renderPoint(float x, float y) { SDL_RenderPoint(renderer, x, y); }
	export void renderPoints(const Point* points, float count) { SDL_RenderPoints(renderer, points, count); }
	export void renderRect(const RectF* rect) { SDL_RenderRect(renderer, rect); }
	export void renderRects(const RectF* rects, int count) { SDL_RenderRects(renderer, rects, count); }
	export void renderFillRect(const RectF* rect) { SDL_RenderFillRect(renderer, rect); }
	export void renderFillRects(const RectF* rects, int count) { SDL_RenderFillRects(renderer, rects, count); }
	export void renderGetBlendMode(SDL_BlendMode* blendMode) { SDL_GetRenderDrawBlendMode(renderer, blendMode); }
	export void renderGetClipRect(SDL_Rect* rect) { SDL_GetRenderClipRect(renderer, rect); }
	export void renderGetDrawColor(Uint8* r, Uint8* g, Uint8* b, Uint8* a) { SDL_GetRenderDrawColor(renderer, r, g, b, a); }
	export void renderGetScale(float* scaleX, float* scaleY) { SDL_GetRenderScale(renderer, scaleX, scaleY); }
	export void renderGetViewport(SDL_Rect* rect) { SDL_GetRenderViewport(renderer, rect); }
	export SDL_bool renderIsClipEnabled() { return SDL_RenderClipEnabled(renderer); }
	export void renderPresent() { SDL_RenderPresent(renderer); }
	export void renderSetBlendMode(SDL_BlendMode blendMode) { SDL_SetRenderDrawBlendMode(renderer, blendMode); }
	export void renderSetClipRect(const RectI* rect) { SDL_SetRenderClipRect(renderer, rect); }
	export void renderSetDrawColor(const Color& c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }
	export void renderSetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { SDL_SetRenderDrawColor(renderer, r, g, b, a); }
	export void renderSetScale(float scaleX, float scaleY) { SDL_SetRenderScale(renderer, scaleX, scaleY); }
	export void renderSetViewport(const RectI* rect) { SDL_SetRenderViewport(renderer, rect); }

	/* Surface functions */
	export int surfaceBlit(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_BlitSurface(src, srcrect, dst, dstrect); }
	export int surfaceBlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect, SDL_ScaleMode mode) { return SDL_BlitSurfaceScaled(src, srcrect, dst, dstrect, mode); }
	export int surfaceFillRect(SDL_Surface* surface, const SDL_Rect* rect, Uint32 color) { return SDL_FillSurfaceRect(surface, rect, color); }
	export int surfaceFillRects(SDL_Surface* surface, const SDL_Rect* rects, int count, Uint32 color) { return SDL_FillSurfaceRects(surface, rects, count, color); }
	export int surfaceLock(SDL_Surface* surface) { return SDL_LockSurface(surface); }
	export int surfaceSetAlphaMod(SDL_Surface* surface, Uint8 alpha) { return SDL_SetSurfaceAlphaMod(surface, alpha); }
	export int surfaceSetBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode) { return SDL_SetSurfaceBlendMode(surface, blendMode); }
	export int surfaceSetColorKey(SDL_Surface* surface, Uint32 key) { return SDL_SetSurfaceColorKey(surface, SDL_TRUE, key); }
	export int surfaceSetPalette(SDL_Surface* surface, SDL_Palette* palette) { return SDL_SetSurfacePalette(surface, palette); }
	export SDL_Surface* surfaceConvertFormat(SDL_Surface* surface, SDL_PixelFormatEnum pixel_format) { return SDL_ConvertSurfaceFormat(surface, pixel_format); }
	export SDL_Surface* surfaceCopy(SDL_Surface* src) { return SDL_DuplicateSurface(src); }
	export SDL_Surface* surfaceCreate(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurface(width, height, SDL_GetPixelFormatEnumForMasks(depth, Rmask, Gmask, Bmask, Amask)); }
	export SDL_Surface* surfaceCreateFrom(void* pixels, int width, int height, int pitch, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateSurfaceFrom(pixels, width, height, pitch, SDL_GetPixelFormatEnumForMasks(depth, Rmask, Gmask, Bmask, Amask)); }
	export SDL_Surface* surfaceLoad(const char* file) { return IMG_Load(file); }
	export void surfaceDestroy(SDL_Surface* surface) { SDL_DestroySurface(surface); }
	export void surfaceUnlock(SDL_Surface* surface) { SDL_UnlockSurface(surface); }

	/* Text rendering functions */
	export SDL_Surface* textRenderBlended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Blended(font, text, fg); }
	export SDL_Surface* textRenderBlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderText_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderShaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderText_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderSolid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderText_Solid(font, text, fg); }
	export SDL_Surface* textRenderUNICODEBlended(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Blended(font, text, fg); }
	export SDL_Surface* textRenderUNICODEBlendedWrapped(TTF_Font* font, const Uint16* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUNICODE_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderUNICODEShaded(TTF_Font* font, const Uint16* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUNICODE_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderUNICODESolid(TTF_Font* font, const Uint16* text, SDL_Color fg) { return TTF_RenderUNICODE_Solid(font, text, fg); }
	export SDL_Surface* textRenderUTF8Blended(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Blended(font, text, fg); }
	export SDL_Surface* textRenderUTF8BlendedWrapped(TTF_Font* font, const char* text, SDL_Color fg, Uint32 wrapLength) { return TTF_RenderUTF8_Blended_Wrapped(font, text, fg, wrapLength); }
	export SDL_Surface* textRenderUTF8Shaded(TTF_Font* font, const char* text, SDL_Color fg, SDL_Color bg) { return TTF_RenderUTF8_Shaded(font, text, fg, bg); }
	export SDL_Surface* textRenderUTF8Solid(TTF_Font* font, const char* text, SDL_Color fg) { return TTF_RenderUTF8_Solid(font, text, fg); }

	/* Texture management functions */
	export int textureGetAlphaMod(Texture* texture, Uint8* alpha) { return SDL_GetTextureAlphaMod(texture, alpha); }
	export int textureGetBlendMode(Texture* texture, SDL_BlendMode* blendMode) { return SDL_GetTextureBlendMode(texture, blendMode); }
	export int textureGetColorMod(Texture* texture, Uint8* r, Uint8* g, Uint8* b) { return SDL_GetTextureColorMod(texture, r, g, b); }
	export int textureLock(Texture* texture, const RectI* rect, void** pixels, int* pitch) { return SDL_LockTexture(texture, rect, pixels, pitch); }
	export int textureQuery(Texture* texture, SDL_PixelFormatEnum* format, int* access, int* w, int* h) { return SDL_QueryTexture(texture, format, access, w, h); }
	export int textureSetAlphaMod(Texture* texture, Uint8 alpha) { return SDL_SetTextureAlphaMod(texture, alpha); }
	export int textureSetBlendMode(Texture* texture, SDL_BlendMode blendMode) { return SDL_SetTextureBlendMode(texture, blendMode); }
	export int textureSetColorMod(Texture* texture, const Color& color) { return SDL_SetTextureColorMod(texture, color.r, color.g, color.b); }
	export int textureSetColorMod(Texture* texture, Uint8 r, Uint8 g, Uint8 b) { return SDL_SetTextureColorMod(texture, r, g, b); }
	export int textureSetRenderTarget(Texture* texture) { return SDL_SetRenderTarget(renderer, texture); }
	export int textureUpdate(Texture* texture, const RectI* rect, const void* pixels, int pitch) { return SDL_UpdateTexture(texture, rect, pixels, pitch); }
	export int textureUpdateYUV(Texture* texture, const RectI* rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch) { return SDL_UpdateYUVTexture(texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch); }
	export Texture* textureCreate(SDL_PixelFormatEnum format, int access, int w, int h) { return SDL_CreateTexture(renderer, format, access, w, h); }
	export Texture* textureCreateFromSurface(SDL_Surface* surface) { return SDL_CreateTextureFromSurface(renderer, surface); }
	export Texture* textureLoad(const char* path) { return IMG_LoadTexture(renderer, path); }
	export void textureDestroy(Texture* texture) { SDL_DestroyTexture(texture); }
	export void textureUnlock(Texture* texture) { SDL_UnlockTexture(texture); }

	/* Window functions */
	export const char* windowGetTitle() { return SDL_GetWindowTitle(window); }
	export int windowGetOpacity(float* out_opacity) { return SDL_GetWindowOpacity(window, out_opacity); }
	export int windowSetFullscreen(Uint32 flags) { return SDL_SetWindowFullscreen(window, flags); }
	export int windowUpdateSurface() { return SDL_UpdateWindowSurface(window); }
	export SDL_bool windowGetMouseGrab() { return SDL_GetWindowMouseGrab(window); }
	export SDL_Renderer* windowCreateRenderer(Uint32 flags) { return SDL_CreateRenderer(window, nullptr, flags); }
	export SDL_Surface* windowGetSurface() { return SDL_GetWindowSurface(window); }
	export SDL_Window* windowCreate(const char* title, int w, int h, Uint32 flags) { return SDL_CreateWindow(title, w, h, flags); }
	export Uint32 windowGetFlags() { return SDL_GetWindowFlags(window); }
	export void windowGetPosition(int* x, int* y) { SDL_GetWindowPosition(window, x, y); }
	export void windowGetSize(int* w, int* h) { SDL_GetWindowSize(window, w, h); }
	export void windowHide() { SDL_HideWindow(window); }
	export void windowMaximize() { SDL_MaximizeWindow(window); }
	export void windowMinimize() { SDL_MinimizeWindow(window); }
	export void windowRaise() { SDL_RaiseWindow(window); }
	export void windowRestore() { SDL_RestoreWindow(window); }
	export void windowSetIcon(SDL_Surface* icon) { SDL_SetWindowIcon(window, icon); }
	export void windowSetModalFor(SDL_Window* modal_window, SDL_Window* parent_window) { SDL_SetWindowModalFor(modal_window, parent_window); }
	export void windowSetMouseGrab(SDL_bool grabbed) { SDL_SetWindowMouseGrab(window, grabbed); }
	export void windowSetOpacity(float opacity) { SDL_SetWindowOpacity(window, opacity); }
	export void windowSetPosition(int x, int y) { SDL_SetWindowPosition(window, x, y); }
	export void windowSetSize(int w, int h) { SDL_SetWindowSize(window, w, h); }
	export void windowSetTitle(const char* title) { SDL_SetWindowTitle(window, title); }
	export void windowShow() { SDL_ShowWindow(window); }

	/* Misc functions */
	export int ticks() { return SDL_GetTicksNS(); }
	export const char* __cdecl getError() { return TTF_GetError(); }
	export template <typename... Args> void log(SDL_LogPriority priority, const char* message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message, args...); }
	export template <typename... Args> void log(SDL_LogPriority priority, std::string_view message, const Args&... args) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.data(), args...); }
	export template <typename... Args> void logError(const char* message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }
	export template <typename... Args> void logError(std::string_view message, const Args&... args) { log(SDL_LOG_PRIORITY_ERROR, message, args...); }


	/* When using a fixed framerate, sleep to fill up remaining time */
	export void capFrame(int fps) {
		Uint32 delta = ticks() - timeStart;
		Uint32 frameDur = (1000 / fps);
		if (frameDur > delta) {
			SDL_Delay(frameDur - delta);
		}
	}

	/* Set up SDL. Returns true if SDL setup succeeds */
	export bool initSDL() { 
		int val = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);
		if (val < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_INIT failed with value %d", val);
			return false;
		}

		val = IMG_Init(IMG_INIT_PNG);
		if (val == 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init failed with value %d", val);
			return false;
		}

		if (TTF_Init() < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed");
			return false;
		}

		// TODO adjust spec as needed
		if (Mix_OpenAudio(0, nullptr) < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio failed");
			return false;
		}

		// Initialize keyboard and pad
		key = SDL_GetKeyboardState(&numKeys);
		keyLast = new Uint8[numKeys];
		memcpy(keyLast, key, numKeys);

		// TODO pad

		return true;
	}

	/* Set up window and renderer. Returns true if window and renderer were created */
	export bool initWindow(int w, int h, Uint32 windowFlags = 0, bool vsync = false, const char* title = "Fabricate") {
		window = windowCreate(title, w, h, windowFlags);
		renderer = SDL_CreateRenderer(window, nullptr, vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
		if (!window || !renderer) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Window or renderer went derp");
			SDL_Quit();
			return false;
		}
		return true;
	}

	/* Update the renderer with the VSync settings */
	export void updateWindow(bool vsync) {
		SDL_DestroyRenderer(renderer);
		renderer = SDL_CreateRenderer(window, nullptr, vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
	}

	/* 
	Execute a singular game loop
	Returns false if the program should terminate 
	*/
	export bool poll() {
		// Update temporary states
		timeStart = ticks();
		mouseLast = mouse;
		std::memcpy(keyLast, key, numKeys);

		// Update input events
		int res = SDL_PollEvent(&e);
		key = SDL_GetKeyboardState(nullptr);

		if (res != 0) {
			switch (e.type) {
			case SDL_EVENT_QUIT:
				return false;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				mouse = e.button.button;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				mouse = -1;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			// Key down: If a listener is present, special keys will trigger listeners. These keys are independent of hotkey settings
			case SDL_EVENT_KEY_DOWN:
				if (kListener) {
					switch (e.key.keysym.sym) {
					case SDLK_DOWN:
						kListener->onArrowUp();
						break;
					case SDLK_LEFT:
						kListener->onArrowLeft();
						break;
					case SDLK_RIGHT:
						kListener->onArrowRight();
						break;
					case SDLK_UP:
						kListener->onArrowUp();
						break;
					case SDLK_BACKSPACE:
						kListener->onBackspace();
						break;
					case SDLK_KP_ENTER:
						kListener->onEnter();
						break;
					case SDLK_ESCAPE:
						kListener->onEsc();
						keyboardInputStop();
						break;
					}
				}
				break;
			case SDL_EVENT_TEXT_INPUT:
				if (kListener) {
					kListener->onTextInput(e.text.text);
				}
				break;
				// TODO file dialog
			case SDL_EVENT_DROP_FILE:
				break;
			}
		}

		return true;
	}

	/* Clean up SDL */
	export void quit() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		renderer = nullptr;
		window = nullptr;
		TTF_Quit();
		IMG_Quit();
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
	}
}