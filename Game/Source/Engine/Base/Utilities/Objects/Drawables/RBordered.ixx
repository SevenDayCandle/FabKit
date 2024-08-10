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
		sdl::queueDrawBordered(cb, rp, texture, tint, x, y, w, h, rotation, pipeline);
	}
}
