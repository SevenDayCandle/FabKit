export module fab.EmptyDrawable;

import fab.FUtil;
import fab.IDrawable;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

/* A dummy drawable, to be used in place of a drawable when nothing should be drawn */
namespace fab {
	export class EmptyDrawable : public IDrawable {
	public:
		EmptyDrawable() {}

		inline void drawCentered(BatchRenderPass& rp, float x, float y, float w, float h, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {}
	} EMPTY;
}
