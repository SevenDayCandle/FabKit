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
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::GpuGraphicsPipeline* pipeline) override {}
	};
}