export module fbc.RHorizontal;

import fbc.FTexture;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class RHorizontal : public FTexture {
	public:
		RHorizontal(strv path) : FTexture(path) {}
		RHorizontal(const RHorizontal&) = delete;

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) override;
	};

	void RHorizontal::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) {
		sdl::queueDrawHorizontal(cb, rp, texture, destRec, tint, pipeline);
	}
}
