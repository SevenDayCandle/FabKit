export module fbc.RBordered;

import fbc.FUtil;
import fbc.FTexture;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class RBordered : public FTexture {
	public:
		RBordered(strv path) : FTexture(path) {}
		RBordered(const RBordered&) = delete;

		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, (x + 0.5f * scX * w) / winW, (y + 0.5f * scY * h) / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
		inline void drawCentered(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawPatches(rp, x / winW, y / winH, w, h, winW, winH, scX, scY, rotZ, tint, pipeline);
		}
	private:
		void drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL);
	};

	void RBordered::drawPatches(sdl::SDLBatchRenderPass& rp, float centerX, float centerY, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float cornerSX = scX * texW / (2 * winW);
		const float cornerSY = scY * texH / (2 * winH);
		const float edgeSX = scX * (w - texW) / winW;
		const float edgeSY = scY * (h - texH) / winH;

		const float distX = (edgeSX + cornerSX) / 2;
		const float distY = (edgeSY + cornerSY) / 2;

		const float beginX = centerX - distX;
		const float beginY = centerY - distY;
		const float endX = centerX + distX;
		const float endY = centerY + distY;

		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX_BORDERED);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));

		rp.setupVertexUniform(beginX, beginY, cornerSX, cornerSY, rotZ); // Top Left
		rp.drawIndexedPrimitives(0);
		rp.setupVertexUniform(centerX, beginY, edgeSX, cornerSY, rotZ); // Top
		rp.drawIndexedPrimitives(4);
		rp.setupVertexUniform(endX, beginY, cornerSX, cornerSY, rotZ); // Top Right
		rp.drawIndexedPrimitives(8);
		rp.setupVertexUniform(beginX, centerY, cornerSX, edgeSY, rotZ); // Center Left
		rp.drawIndexedPrimitives(12);
		rp.setupVertexUniform(centerX, centerY, edgeSX, edgeSY, rotZ); // Center
		rp.drawIndexedPrimitives(16);
		rp.setupVertexUniform(endX, centerY, cornerSX, edgeSY, rotZ); // Center Right
		rp.drawIndexedPrimitives(20);
		rp.setupVertexUniform(beginX, endY, cornerSX, cornerSY, rotZ); // Bottom Left
		rp.drawIndexedPrimitives(24);
		rp.setupVertexUniform(centerX, endY, edgeSX, cornerSY, rotZ); // Bottom
		rp.drawIndexedPrimitives(28);
		rp.setupVertexUniform(endX, endY, cornerSX, cornerSY, rotZ); // Bottom Right
		rp.drawIndexedPrimitives(32);
	}
}
