export module fbc.EmptyDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import std;

namespace fbc {
	constexpr sdl::RectF EMPTY = { 0,0,0,0 };

	export class EmptyDrawable : public IDrawable {
	public:
		EmptyDrawable() {}

		inline float getHeight() const override { return 0; }
		inline float getWidth() const override { return 0; }
		inline void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) override {}
	};
}