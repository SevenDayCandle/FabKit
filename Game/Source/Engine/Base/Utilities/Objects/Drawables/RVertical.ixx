export module fbc.RVertical;

import fbc.FTexture;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class RVertical : public FTexture {
	public:
		RVertical(strv path) : FTexture(path) {}
		RVertical(const RVertical&) = delete;

		void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override;
	};

	void RVertical::draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		const float cornerW = texW / 2;
		const float edgeH = h - texW;
		const float centerY = y + cornerW;

		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, y, w, cornerW, winW, winH, rotZ, tint, pipeline, 0); // Top
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, centerY, w, edgeH, winW, winH, rotZ, tint, pipeline, 4); // Center
		ImageDrawable::draw(rp, sdl::runner::BUFFER_VERTEX_BORDERED, x, centerY + edgeH, w, cornerW, winW, winH, rotZ, tint, pipeline, 8); // Bottom
	}
}
