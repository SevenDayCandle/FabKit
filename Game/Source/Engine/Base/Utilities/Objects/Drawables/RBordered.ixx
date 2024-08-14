export module fbc.RBordered;

import fbc.FUtil;
import fbc.FTexture;
import sdl;
import std;

namespace fbc {
	export class RBordered : public FTexture {
	public:
		RBordered(strv path) : FTexture(path) {}
		RBordered(const RBordered&) = delete;

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) override;
	};

	void RBordered::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) {
		const float cornerW = texW / 2;
		const float edgeW = w - texW;
		const float edgeH = h - texW;
		const float centerX = x + cornerW;
		const float centerY = y + cornerW;
		const float endX = centerX + edgeW;
		const float endY = centerY + edgeH;

		sdl::queueDrawBordered(cb, rp, texture, tint, x, y, cornerW, cornerW, rotation, pipeline, 0); // Top Left
		sdl::queueDrawBordered(cb, rp, texture, tint, centerX, y, edgeW, cornerW, rotation, pipeline, 4); // Top
		sdl::queueDrawBordered(cb, rp, texture, tint, endX, y, cornerW, cornerW, rotation, pipeline, 8); // Top Right
		sdl::queueDrawBordered(cb, rp, texture, tint, x, centerY, cornerW, edgeH, rotation, pipeline, 12); // Center Left
		sdl::queueDrawBordered(cb, rp, texture, tint, centerX, centerY, edgeW, edgeH, rotation, pipeline, 16); // Center
		sdl::queueDrawBordered(cb, rp, texture, tint, endX, centerY, cornerW, edgeH, rotation, pipeline, 20); // Center Right
		sdl::queueDrawBordered(cb, rp, texture, tint, x, endY, cornerW, cornerW, rotation, pipeline, 24); // Bottom Left
		sdl::queueDrawBordered(cb, rp, texture, tint, centerX, endY, edgeW, cornerW, rotation, pipeline, 28); // Bottom
		sdl::queueDrawBordered(cb, rp, texture, tint, endX, endY, cornerW, cornerW, rotation, pipeline, 32); // Bottom Right
	}
}
