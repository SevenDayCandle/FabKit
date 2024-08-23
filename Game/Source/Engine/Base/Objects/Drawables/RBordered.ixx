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

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RBordered::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float cornerW = texW / 2;
		const float edgeW = w - texW;
		const float edgeH = h - texW;
		const float centerX = x + cornerW;
		const float centerY = y + cornerW;
		const float endX = centerX + edgeW;
		const float endY = centerY + edgeH;

		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, y, cornerW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 0); // Top Left
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerX, y, edgeW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 4); // Top
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endX, y, cornerW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 8); // Top Right
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, centerY, cornerW, edgeH, winW, winH, scX, scY, rotZ, tint, pipeline, 12); // Center Left
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerX, centerY, edgeW, edgeH, winW, winH, scX, scY, rotZ, tint, pipeline, 16); // Center
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endX, centerY, cornerW, edgeH, winW, winH, scX, scY, rotZ, tint, pipeline, 20); // Center Right
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, endY, cornerW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 24); // Bottom Left
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerX, endY, edgeW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 28); // Bottom
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endX, endY, cornerW, cornerW, winW, winH, scX, scY, rotZ, tint, pipeline, 32); // Bottom Right
	}
}
