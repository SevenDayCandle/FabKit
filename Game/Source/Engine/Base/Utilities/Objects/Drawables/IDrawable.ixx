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

		virtual void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::RectF& destRec, sdl::GpuGraphicsPipeline* pipeline = sdl::RENDER_STANDARD, const sdl::Color* tint = &sdl::COLOR_WHITE, float rotation = 0, float flipX = 1, float flipY = 1) = 0;
		virtual float getHeight() const = 0;
		virtual float getWidth() const = 0;
	};
}