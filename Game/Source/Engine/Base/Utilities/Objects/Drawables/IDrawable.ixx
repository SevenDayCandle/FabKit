export module fbc.IDrawable;

import fbc.FUtil;
import fbc.ILoadable;
import sdl;

namespace fbc {
	export struct IDrawable : public ILoadable {
	public:
		IDrawable() {}
		virtual ~IDrawable() override = default;

		inline virtual void dispose() override {}
		inline virtual void reload() const override {}
		inline void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& rect, const sdl::Color* tint = &sdl::COLOR_STANDARD, float rotation = 0, sdl::GpuGraphicsPipeline* pipeline = sdl::RENDER_STANDARD) {
			draw(cb, rp, tint, rect.x, rect.y, rect.w, rect.h, rotation, pipeline);
		};

		virtual void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation = 0, sdl::GpuGraphicsPipeline* pipeline = sdl::RENDER_STANDARD) = 0;
		virtual float getHeight() const = 0;
		virtual float getWidth() const = 0;
	};
}