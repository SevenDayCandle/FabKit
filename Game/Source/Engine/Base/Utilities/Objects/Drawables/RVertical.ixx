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
		sdl::queueDrawHorizontal(cb, rp, texture, tint, x, y, w, h, rotation, pipeline);
	}
}
