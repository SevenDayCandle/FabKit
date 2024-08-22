export module fbc.RectDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class RectDrawable : public IDrawable {
	public:
		RectDrawable() {}
		virtual ~RectDrawable() = default;

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RectDrawable::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline)
	{
		setupMatrix(x, y, w, h, scX, scY, winW, winH, rotZ);
		rp.bindPipeline(sdl::runner::shapePipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.pushVertexUniform(&MATRIX_UNIFORM, sizeof(sdl::Matrix4x4));
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives(0);
	}
}
