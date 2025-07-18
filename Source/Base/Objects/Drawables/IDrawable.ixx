export module fab.IDrawable;

import fab.FUtil;
import fab.ILoadable;
import sdl.SDLBase; 
import fab.BatchRenderPass;
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
		inline void dispose() override {} // Should be called when this drawable will no longer be used
		inline void reload() const override {} // Called to initialize this drawable for rendering. Calling this function again after initialization will dispose of the previous initialization and reinitialize the drawable
		inline void draw(BatchRenderPass& rp, const sdl::RectF& rect, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			draw(rp, rect.x, rect.y, rect.w, rect.h, scX, scY, rotZ, tint, pipeline);
		};
		inline void draw(BatchRenderPass& rp, float x, float y, float w, float h, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawCentered(rp, (x + 0.5f * w), (y + 0.5f * h), w, h, scX, scY, rotZ, tint, pipeline);
		}
		inline void drawCenteredFull(BatchRenderPass& rp, float x, float y, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawCentered(rp, x, y, getWidth(), getHeight(), scX, scY, rotZ, tint, pipeline);
		}
		inline void drawFull(BatchRenderPass& rp, const pair<int, int>& coords, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			draw(rp, coords.first, coords.second, getWidth(), getHeight(), scX, scY, rotZ, tint, pipeline);
		};
		inline void drawFull(BatchRenderPass& rp, float x, float y, float scX = 1, float scY = 1, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			draw(rp, x, y, getWidth(), getHeight(), scX, scY, rotZ, tint, pipeline);
		};

		virtual void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) = 0;
	};
}