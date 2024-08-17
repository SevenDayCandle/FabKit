export module fbc.IDrawable;

import fbc.FUtil;
import fbc.ILoadable;
import sdl;
import sdl.SDLBatchRenderPass;

namespace fbc {
	export struct IDrawable : public ILoadable {
	public:
		IDrawable() {}
		virtual ~IDrawable() override = default;

		inline virtual void dispose() override {}
		inline virtual void reload() const override {}
		inline void draw(sdl::SDLBatchRenderPass& rp, const sdl::RectF& rect, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::GpuGraphicsPipeline* pipeline = sdl::runner::RENDER_STANDARD) {
			draw(rp, rect.x, rect.y, rect.w, rect.h, winW, winH, rotZ, tint, pipeline);
		};

		virtual void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::GpuGraphicsPipeline* pipeline = sdl::runner::RENDER_STANDARD) = 0;
		virtual float getHeight() const = 0;
		virtual float getWidth() const = 0;
	protected:
		inline static sdl::Matrix4x4 MATRIX_UNIFORM = {
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};
}