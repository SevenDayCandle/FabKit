export module fab.RVertical;

import fab.FTexture;
import fab.FUtil;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;

namespace fab {
	export class RVertical : public FTexture {
	public:
		RVertical(strv path) : FTexture(path) {}
		RVertical(const RVertical&) = delete;

		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, (x + 0.5f * w) / winW, (y + 0.5f * h) / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
		inline void drawCentered(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, x / winW, y / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
	private:
		void drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL);
	};

	void RVertical::drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sX = scX * w / winW;
		const float cornerSY = scY * texH / (2 * winH);
		const float edgeSY = scY * (h - texH) / winH;

		const float distY = (edgeSY + cornerSY) / 2;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX_VERTICAL);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));

		rp.setupVertexUniform(centerX, centerY - distY, sX, cornerSY, rotZ); // Top
		rp.drawIndexedPrimitives(0);
		rp.setupVertexUniform(centerX, centerY, sX, edgeSY, rotZ); // Center
		rp.drawIndexedPrimitives(4);
		rp.setupVertexUniform(centerX, centerY + distY, sX, cornerSY, rotZ); // Bottom
		rp.drawIndexedPrimitives(8);
	}
}
