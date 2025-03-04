export module fab.RectDrawable;

import fab.FUtil;
import fab.IDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

/* Represents a solid rectangle to be rendered on screen */
namespace fab {
	export class RectDrawable : public IDrawable {
	public:
		RectDrawable() {}
		virtual ~RectDrawable() = default;

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RectDrawable::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline)
	{
		// Assume origin is at the center of the drawable
		float sX = scX * w / winW;
		float sY = scY * h / winH;
		rp.bindPipeline(sdl::runner::shapePipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.setupVertexUniform((x / winW) + 0.5 * sX, (y / winH) + 0.5 * sY, sX, sY, rotZ);
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives(0);
	}
}
