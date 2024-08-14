export module fbc.RVertical;

import fbc.FTexture;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class RVertical : public FTexture {
	public:
		RVertical(strv path) : FTexture(path) {}
		RVertical(const RVertical&) = delete;

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) override;
	};

	void RVertical::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) {
		const float cornerW = texW / 2;
		const float edgeH = h - texW;
		const float centerY = y + cornerW;

		sdl::queueDrawVertical(cb, rp, texture, tint, x, y, w, cornerW, rotation, pipeline, 0); // Top
		sdl::queueDrawVertical(cb, rp, texture, tint, x, centerY, w, edgeH, rotation, pipeline, 4); // Center
		sdl::queueDrawVertical(cb, rp, texture, tint, x, centerY + edgeH, w, cornerW, rotation, pipeline, 8); // Bottom
	}
}
