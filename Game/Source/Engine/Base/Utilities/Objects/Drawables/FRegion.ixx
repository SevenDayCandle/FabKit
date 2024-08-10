export module fbc.FRegion;

import fbc.FTexture;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;

namespace fbc {
	export class FRegion : public IDrawable {
	public:
		FRegion(FTexture& base, sdl::RectF dim) {}

		inline float getHeight() const override { return 0; }
		inline float getWidth() const override { return 0; }

		void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) override;
	};

	void FRegion::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline, const sdl::Color* tint, float rotation, float flipX, float flipY) {
		// TODO implement
	}
}