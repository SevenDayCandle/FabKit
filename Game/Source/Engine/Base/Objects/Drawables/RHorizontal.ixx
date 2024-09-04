export module fbc.RHorizontal;

import fbc.FTexture;
import fbc.FUtil;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;

namespace fbc {
	export class RHorizontal : public FTexture {
	public:
		RHorizontal(strv path) : FTexture(path) {}
		RHorizontal(const RHorizontal&) = delete;

		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, (x + 0.5f * scX * w) / winW, (y + 0.5f * scY * h) / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
		inline void drawCentered(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, x / winW, y / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
	private:
		void drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL);
	};

	void RHorizontal::drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sY = scY * h / winH;
		const float cornerSX = scX * texW / (2 * winW);
		const float edgeSX = scX * (w - texW) / winW;

		const float distX = (edgeSX + cornerSX) / 2;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX_HORIZONTAL);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));

		rp.setupVertexUniform(centerX - distX, centerY, cornerSX, sY, rotZ); // Left
		rp.drawIndexedPrimitives(0);
		rp.setupVertexUniform(centerX, centerY, edgeSX, sY, rotZ); // Center
		rp.drawIndexedPrimitives(4);
		rp.setupVertexUniform(centerX + distX, centerY, cornerSX, sY, rotZ); // Right
		rp.drawIndexedPrimitives(8);
	}
}
