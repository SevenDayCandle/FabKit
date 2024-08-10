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

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) override;
	};

	void RBordered::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) {
		sdl::queueDrawBordered(cb, rp, texture, destRec, tint, pipeline);
	}
}
