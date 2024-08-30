export module fbc.RVertical;

import fbc.FTexture;
import fbc.FUtil;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;

namespace fbc {
	export class RVertical : public FTexture {
	public:
		RVertical(strv path) : FTexture(path) {}
		RVertical(const RVertical&) = delete;

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RVertical::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float sX = scX * w / winW;
		const float sY = scY * h / winH;
		const float tY = y / winH;

		const float cornerS = scX * texW / (2 * winW);
		const float cornerO = cornerS / 2;
		const float edgeSY = sY - 2 * cornerS;
		const float centerTY = tY + cornerS;

		const float tXO = x / winW + sX / 2;

		drawImpl(rp, sdl::runner::BUFFER_VERTEX_VERTICAL, tXO, tY + cornerO, sX, cornerS, rotZ, tint, pipeline, 0); // Top
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_VERTICAL, tXO, centerTY + edgeSY / 2, sX, edgeSY, rotZ, tint, pipeline, 4); // Center
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_VERTICAL, tXO, centerTY + edgeSY + cornerO, sX, cornerS, rotZ, tint, pipeline, 8); // Bottom
	}
}
