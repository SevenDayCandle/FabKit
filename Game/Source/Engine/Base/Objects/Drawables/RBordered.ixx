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
		const float sX = scX * w / winW;
		const float sY = scY * h / winH;
		const float tX = x / winW;
		const float tY = y / winH;

		const float cornerS = scX * texW / (2 * winW);
		const float cornerO = cornerS / 2;

		const float edgeSX = sX - 2 * cornerS;
		const float edgeSY = sY - 2 * cornerS;
		const float centerTX = tX + cornerS;
		const float centerTY = tY + cornerS;
		const float endTXO = centerTX + edgeSX + cornerO;
		const float endTYO = centerTY + edgeSY + cornerO;
		const float centerTXO = centerTX + edgeSX / 2;
		const float centerTYO = centerTY + edgeSY / 2;

		const float tXO = tX + cornerO;
		const float tYO = tY + cornerO;

		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, tXO, tYO, cornerS, cornerS, rotZ, tint, pipeline, 0); // Top Left
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerTXO, tYO, edgeSX, cornerS, rotZ, tint, pipeline, 4); // Top
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endTXO, tYO, cornerS, cornerS, rotZ, tint, pipeline, 8); // Top Right
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, tXO, centerTYO, cornerS, edgeSY, rotZ, tint, pipeline, 12); // Center Left
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerTXO, centerTYO, edgeSX, edgeSY, rotZ, tint, pipeline, 16); // Center
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endTXO, centerTYO, cornerS, edgeSY, rotZ, tint, pipeline, 20); // Center Right
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, tXO, endTYO, cornerS, cornerS, rotZ, tint, pipeline, 24); // Bottom Left
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, centerTXO, endTYO, edgeSX, cornerS, rotZ, tint, pipeline, 28); // Bottom
		drawImpl(rp, sdl::runner::BUFFER_VERTEX_BORDERED, endTXO, endTYO, cornerS, cornerS,  rotZ, tint, pipeline, 32); // Bottom Right
	}
}
