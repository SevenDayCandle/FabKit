export module fbc.RVertical;

import fbc.FTexture;
import fbc.FUtil;
import sdl;

namespace fbc {
	export class RVertical : public FTexture {
	public:
		RVertical(strv path) : FTexture(path) {}
		RVertical(const RVertical&) = delete;

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) override;
	};

	void RVertical::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) {
		sdl::queueDrawHorizontal(cb, rp, texture, destRec, tint, pipeline);
	}
}
