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

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RHorizontal::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float cornerW = texW / 2;
		const float edgeW = w - texW;
		const float centerX = x + cornerW;

		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, y, cornerW, h, winW, winH, rotZ, tint, pipeline, 0); // Left
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerX, y, edgeW, h, winW, winH, rotZ, tint, pipeline, 4); // Center
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerX + edgeW, y, cornerW, h, winW, winH, rotZ, tint, pipeline, 8); // Right
	}
}
