export module fab.IDrawable;

import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

/* An interface for an object that can be rendered to a window */
namespace fab {
	export struct IDrawable : public ILoadable {
	public:
		IDrawable() {}
		virtual ~IDrawable() override = default;

		inline virtual float getHeight() const { return 0; }
		inline virtual float getWidth() const { return 0; }
		inline virtual void dispose() override {} // Should be called when this drawable will no longer be used
		inline virtual void reload() const override {} // Called to initialize this drawable for rendering. Calling this function again after initialization will dispose of the previous initialization and reinitialize the drawable
		inline void draw(sdl::SDLBatchRenderPass& rp, const sdl::RectF& rect, float winW, float winH, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			draw(rp, rect.x, rect.y, rect.w, rect.h, winW, winH, scX, scY, rotZ, tint, pipeline);
		};

		virtual void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) = 0;
	};
}