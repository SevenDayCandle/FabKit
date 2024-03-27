module;

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

export module sdl;

import std;

int mouse = -1;
int mouseLast = -1;
int mousePosX;
int mousePosY;
SDL_Event e;
SDL_Renderer* renderer;
SDL_Window* window;
Uint32 timeStart;

export namespace sdl {

	export using BlendMode = ::SDL_BlendMode;
	export using Color = ::SDL_Color;
	export using Font = ::TTF_Font;
	export using Point = ::SDL_FPoint;
	export using PointI = ::SDL_Point;
	export using RectF = ::SDL_FRect;
	export using RectI = ::SDL_Rect;
	export using RendererFlip = ::SDL_RendererFlip;
	export using Surface = ::SDL_Surface;
	export using Texture = ::SDL_Texture;

	/* Color constants */
	export constexpr Color BLACK = { 0, 0, 0, 255 };
	export constexpr Color GRAY = { 127, 127, 127, 255 };
	export constexpr Color WHITE = { 255, 255, 255, 255 };

	/* Directory stuff */
	export char* dirBase() { return SDL_GetBasePath(); }
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
	export TTF_Font* fontOpenIndexRW(SDL_RWops* src, int freesrc, int ptsize, long index) { return TTF_OpenFontIndexRW(src, freesrc, ptsize, index); }
	export TTF_Font* fontOpenRW(SDL_RWops* src, int freesrc, int ptsize) { return TTF_OpenFontRW(src, freesrc, ptsize); }
	export int fontOutlineGet(TTF_Font* font) { return TTF_GetFontOutline(font); }
	export void fontOutlineSet(TTF_Font* font, int outline) { TTF_SetFontOutline(font, outline); }
	export int fontSizeText(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeText(font, text, w, h); }
	export int fontSizeUNICODE(TTF_Font* font, const Uint16* text, int* w, int* h) { return TTF_SizeUNICODE(font, text, w, h); }
	export int fontSizeUTF8(TTF_Font* font, const char* text, int* w, int* h) { return TTF_SizeUTF8(font, text, w, h); }
	export int fontStyleIsSet(TTF_Font* font, int style) { return TTF_GetFontStyle(font) & style; }
	export void fontStyleSet(TTF_Font* font, int style) { TTF_SetFontStyle(font, style); }


	/* Mouse state functions */
	export int mouseGetX() { return mousePosX; }
	export int mouseGetY() { return mousePosY; }
	export bool mouseIsLeftClicked() { return mouse == SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustClicked() { return mouse == SDL_BUTTON_LEFT && mouseLast != SDL_BUTTON_LEFT; }
	export bool mouseIsLeftJustReleased() { return mouse != SDL_BUTTON_LEFT && mouseLast == SDL_BUTTON_LEFT; }
	export bool mouseIsRightClicked() { return mouse == SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustClicked() { return mouse == SDL_BUTTON_RIGHT && mouseLast != SDL_BUTTON_RIGHT; }
	export bool mouseIsRightJustReleased() { return mouse != SDL_BUTTON_RIGHT && mouseLast == SDL_BUTTON_RIGHT; }

	/* Rendering functions */
	export void renderClear() { SDL_RenderClear(renderer); }
	export void renderCopy(Texture* texture, const RectI* srcrect, const RectF* dstrect) { SDL_RenderCopyF(renderer, texture, srcrect, dstrect); }
	export void renderCopyEx(Texture* texture, const RectI* srcrect, const RectF* dstrect, const double angle, const Point* center, const SDL_RendererFlip flip) { SDL_RenderCopyExF(renderer, texture, srcrect, dstrect, angle, center, flip); }
	export void renderDrawLine(float x1, float y1, float x2, float y2) { SDL_RenderDrawLineF(renderer, x1, y1, x2, y2); }
	export void renderDrawLines(const Point* points, int count) { SDL_RenderDrawLinesF(renderer, points, count); }
	export void renderDrawPoint(float x, float y) { SDL_RenderDrawPointF(renderer, x, y); }
	export void renderDrawPoints(const Point* points, float count) { SDL_RenderDrawPointsF(renderer, points, count); }
	export void renderDrawRect(const RectF* rect) { SDL_RenderDrawRectF(renderer, rect); }
	export void renderDrawRects(const RectF* rects, int count) { SDL_RenderDrawRectsF(renderer, rects, count); }
	export void renderFillRect(const RectF* rect) { SDL_RenderFillRectF(renderer, rect); }
	export void renderFillRects(const RectF* rects, int count) { SDL_RenderFillRectsF(renderer, rects, count); }
	export void renderGetBlendMode(SDL_BlendMode* blendMode) { SDL_GetRenderDrawBlendMode(renderer, blendMode); }
	export void renderGetClipRect(SDL_Rect* rect) { SDL_RenderGetClipRect(renderer, rect); }
	export void renderGetDrawColor(Uint8* r, Uint8* g, Uint8* b, Uint8* a) { SDL_GetRenderDrawColor(renderer, r, g, b, a); }
	export void renderGetScale(float* scaleX, float* scaleY) { SDL_RenderGetScale(renderer, scaleX, scaleY); }
	export void renderGetViewport(SDL_Rect* rect) { SDL_RenderGetViewport(renderer, rect); }
	export SDL_bool renderIsClipEnabled() { return SDL_RenderIsClipEnabled(renderer); }
	export void renderPresent() { SDL_RenderPresent(renderer); }
	export void renderSetBlendMode(SDL_BlendMode blendMode) { SDL_SetRenderDrawBlendMode(renderer, blendMode); }
	export void renderSetClipRect(const RectI* rect) { SDL_RenderSetClipRect(renderer, rect); }
	export void renderSetDrawColor(const Color& c) { SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); }
	export void renderSetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { SDL_SetRenderDrawColor(renderer, r, g, b, a); }
	export void renderSetScale(float scaleX, float scaleY) { SDL_RenderSetScale(renderer, scaleX, scaleY); }
	export void renderSetViewport(const RectI* rect) { SDL_RenderSetViewport(renderer, rect); }

	/* Surface functions */
	export int surfaceBlit(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_BlitSurface(src, srcrect, dst, dstrect); }
	export int surfaceBlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_BlitScaled(src, srcrect, dst, dstrect); }
	export int surfaceFillRect(SDL_Surface* surface, const SDL_Rect* rect, Uint32 color) { return SDL_FillRect(surface, rect, color); }
	export int surfaceFillRects(SDL_Surface* surface, const SDL_Rect* rects, int count, Uint32 color) { return SDL_FillRects(surface, rects, count, color); }
	export int surfaceLock(SDL_Surface* surface) { return SDL_LockSurface(surface); }
	export int surfaceSetAlphaMod(SDL_Surface* surface, Uint8 alpha) { return SDL_SetSurfaceAlphaMod(surface, alpha); }
	export int surfaceSetBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode) { return SDL_SetSurfaceBlendMode(surface, blendMode); }
	export int surfaceSetColorKey(SDL_Surface* surface, Uint32 key) { return SDL_SetColorKey(surface, SDL_TRUE, key); }
	export int surfaceSetPalette(SDL_Surface* surface, SDL_Palette* palette) { return SDL_SetSurfacePalette(surface, palette); }
	export int surfaceUpperBlit(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_UpperBlit(src, srcrect, dst, dstrect); }
	export int surfaceUpperBlitScaled(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) { return SDL_UpperBlitScaled(src, srcrect, dst, dstrect); }
	export SDL_Surface* surfaceConvertFormat(SDL_Surface* surface, Uint32 pixel_format, Uint32 flags) { return SDL_ConvertSurfaceFormat(surface, pixel_format, flags); }
	export SDL_Surface* surfaceCopy(SDL_Surface* src) { return SDL_DuplicateSurface(src); }
	export SDL_Surface* surfaceCreate(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask); }
	export SDL_Surface* surfaceCreateFrom(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) { return SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask); }
	export SDL_Surface* surfaceLoad(const char* file) { return IMG_Load(file); } // Note: This uses SDL_image, not just SDL
	export void surfaceFree(SDL_Surface* surface) { SDL_FreeSurface(surface); }
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
	export int textureQuery(Texture* texture, Uint32* format, int* access, int* w, int* h) { return SDL_QueryTexture(texture, format, access, w, h); }
	export int textureSetAlphaMod(Texture* texture, Uint8 alpha) { return SDL_SetTextureAlphaMod(texture, alpha); }
	export int textureSetBlendMode(Texture* texture, SDL_BlendMode blendMode) { return SDL_SetTextureBlendMode(texture, blendMode); }
	export int textureSetColorMod(Texture* texture, Uint8 r, Uint8 g, Uint8 b) { return SDL_SetTextureColorMod(texture, r, g, b); }
	export int textureSetRenderTarget(Texture* texture) { return SDL_SetRenderTarget(renderer, texture); }
	export int textureUpdate(Texture* texture, const RectI* rect, const void* pixels, int pitch) { return SDL_UpdateTexture(texture, rect, pixels, pitch); }
	export int textureUpdateYUV(Texture* texture, const RectI* rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch) { return SDL_UpdateYUVTexture(texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch); }
	export Texture* textureCreate(Uint32 format, int access, int w, int h) { return SDL_CreateTexture(renderer, format, access, w, h); }
	export Texture* textureCreateFromSurface(SDL_Surface* surface) { return SDL_CreateTextureFromSurface(renderer, surface); }
	export Texture* textureLoad(const char* path) { return IMG_LoadTexture(renderer, path); }
	export void textureDestroy(Texture* texture) { SDL_DestroyTexture(texture); }
	export void textureUnlock(Texture* texture) { SDL_UnlockTexture(texture); }

	/* Window functions */
	export const char* windowGetTitle() { return SDL_GetWindowTitle(window); }
	export int windowGetOpacity(float* out_opacity) { return SDL_GetWindowOpacity(window, out_opacity); }
	export int windowSetFullscreen(Uint32 flags) { return SDL_SetWindowFullscreen(window, flags); }
	export int windowUpdateSurface() { return SDL_UpdateWindowSurface(window); }
	export SDL_bool windowGetGrab() { return SDL_GetWindowGrab(window); }
	export SDL_Renderer* windowCreateRenderer(int index, Uint32 flags) { return SDL_CreateRenderer(window, index, flags); }
	export SDL_Surface* windowGetSurface() { return SDL_GetWindowSurface(window); }
	export SDL_Window* windowCreate(const char* title, int x, int y, int w, int h, Uint32 flags) { return SDL_CreateWindow(title, x, y, w, h, flags); }
	export Uint32 windowGetFlags() { return SDL_GetWindowFlags(window); }
	export void windowGetPosition(int* x, int* y) { SDL_GetWindowPosition(window, x, y); }
	export void windowGetSize(int* w, int* h) { SDL_GetWindowSize(window, w, h); }
	export void windowHide() { SDL_HideWindow(window); }
	export void windowMaximize() { SDL_MaximizeWindow(window); }
	export void windowMinimize() { SDL_MinimizeWindow(window); }
	export void windowRaise() { SDL_RaiseWindow(window); }
	export void windowRestore() { SDL_RestoreWindow(window); }
	export void windowSetGrab(SDL_bool grabbed) { SDL_SetWindowGrab(window, grabbed); }
	export void windowSetIcon(SDL_Surface* icon) { SDL_SetWindowIcon(window, icon); }
	export void windowSetModalFor(SDL_Window* modal_window, SDL_Window* parent_window) { SDL_SetWindowModalFor(modal_window, parent_window); }
	export void windowSetOpacity(float opacity) { SDL_SetWindowOpacity(window, opacity); }
	export void windowSetPosition(int x, int y) { SDL_SetWindowPosition(window, x, y); }
	export void windowSetSize(int w, int h) { SDL_SetWindowSize(window, w, h); }
	export void windowSetTitle(const char* title) { SDL_SetWindowTitle(window, title); }
	export void windowShow() { SDL_ShowWindow(window); }

	/* Misc functions */
	export int getTicks() { return SDL_GetTicks64(); }
	export void log(SDL_LogPriority priority, std::string_view message) { SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.data()); }
	export void log(SDL_LogPriority priority, const char* message, va_list args) { SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, priority, message, args); }
	export void log(SDL_LogPriority priority, std::string_view message, va_list args) { SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, priority, message.data(), args); }
	export void logError(const char* message, va_list args) { log(SDL_LOG_PRIORITY_ERROR, message, args); }
	export void logError(std::string_view message, va_list args) { log(SDL_LOG_PRIORITY_ERROR, message, args); }


	/* When using a fixed framerate, sleep to fill up remaining time */
	export void capFrame(int fps) {
		Uint32 delta = SDL_GetTicks() - timeStart;
		Uint32 frameDur = (1000 / fps);
		if (frameDur > delta) {
			SDL_Delay(frameDur - delta);
		}
	}

	/* Set up SDL. Returns true if SDL setup succeeds */
	export bool initSDL() { 
		int val = SDL_Init(SDL_INIT_EVERYTHING);
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

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio failed");
			return false;
		}

		return true;
	}

	/* Set up window and renderer. Returns true if window and renderer were created */
	export bool initWindow(int w, int h, Uint32 windowFlags = SDL_WINDOW_SHOWN, bool vsync = false, const char* title = "Fabricate") {
		window = windowCreate(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, windowFlags);
		renderer = SDL_CreateRenderer(window, -1, vsync ? (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) : SDL_RENDERER_ACCELERATED);
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
		renderer = SDL_CreateRenderer(window, -1, vsync ? (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) : SDL_RENDERER_ACCELERATED);
	}

	/* 
	Execute a singular game loop
	Returns false if the program should terminate 
	*/
	export bool poll() {
		// Update temporary states
		timeStart = getTicks();
		mouseLast = mouse;

		// Update input events
		int res = SDL_PollEvent(&e);
		if (res != 0) {
			switch (e.type) {
			case SDL_QUIT:
				return false;
			case SDL_MOUSEBUTTONDOWN:
				mouse = e.button.button;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_MOUSEBUTTONUP:
				mouse = -1;
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
			case SDL_MOUSEMOTION:
				mousePosX = e.button.x;
				mousePosY = e.button.y;
				break;
				// TODO handling for ITextInput
			case SDL_TEXTINPUT:
				break;
				// TODO file dialog
			case SDL_DROPFILE:
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