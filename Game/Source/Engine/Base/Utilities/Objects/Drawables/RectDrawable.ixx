export module fbc.RectDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import std;

namespace fbc {
	export class RectDrawable : public IDrawable {
	public:
		RectDrawable() {}
		virtual ~RectDrawable() = default;

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::GpuGraphicsPipeline* pipeline = sdl::runner::RENDER_STANDARD) override;
	};

	void RectDrawable::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::GpuGraphicsPipeline* pipeline)
	{
		setupMatrix(x, y, w, h, winW, winH, rotZ);
		rp.bindPipeline(pipeline);
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(nullptr, sdl::runner::SAMPLER);
		rp.pushVertexUniform(&MATRIX_UNIFORM, sizeof(sdl::Matrix4x4));
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives(0);
	}
}