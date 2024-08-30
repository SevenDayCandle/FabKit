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

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RHorizontal::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sX = scX * w / winW;
		const float sY = scY * h / winH;
		const float tX = x / winW;

		const float cornerS = scX * texW / (2 * winW);
		const float cornerO = cornerS / 2;
		const float edgeSX = sX - 2 * cornerS;
		const float centerTX = tX + cornerS;
		const float tYO = y / winH + sY / 2;

		drawImpl(rp, sdl::runner::BUFFER_VERTEX_HORIZONTAL, tX + cornerO, tYO, cornerS, sY, rotZ, tint, pipeline, 0); // Left
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_HORIZONTAL, centerTX + edgeSX / 2, tYO, edgeSX, sY, rotZ, tint, pipeline, 4); // Center
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_HORIZONTAL, centerTX + edgeSX + cornerO, tYO, cornerS, sY, rotZ, tint, pipeline, 8); // Right
	}
}
