export module fbc.RHorizontal;

import fbc.FTexture;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class RHorizontal : public FTexture {
	public:
		RHorizontal(strv path) : FTexture(path) {}
		RHorizontal(const RHorizontal&) = delete;

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) override;
	};

	void RHorizontal::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) {
		const float cornerW = texW / 2;
		const float edgeW = w - texW;
		const float centerX = x + cornerW;

		sdl::queueDrawHorizontal(cb, rp, texture, tint, x, y, cornerW, h, rotation, pipeline, 0); // Left
		sdl::queueDrawHorizontal(cb, rp, texture, tint, centerX, y, edgeW, h, rotation, pipeline, 4); // Center
		sdl::queueDrawHorizontal(cb, rp, texture, tint, centerX + edgeW, y, cornerW, h, rotation, pipeline, 8); // Right
	}
}
