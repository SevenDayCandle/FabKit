export module fbc.IDrawable;

import fbc.FUtil;
import fbc.ILoadable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export struct IDrawable : public ILoadable {
	public:
		IDrawable() {}
		virtual ~IDrawable() override = default;

		inline virtual float getHeight() const { return 0; }
		inline virtual float getWidth() const { return 0; }
		inline virtual void dispose() override {} // Should be called when this drawable will no longer be used
		inline virtual void reload() const override {} // Called to initialize this drawable for rendering. Calling this function again after initialization will dispose of the previous initialization and reinitialize the drawable
		inline void draw(sdl::SDLBatchRenderPass& rp, const sdl::RectF& rect, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			draw(rp, rect.x, rect.y, rect.w, rect.h, winW, winH, rotZ, tint, pipeline);
		};

		virtual void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) = 0;
	protected:
		inline static sdl::Matrix4x4 MATRIX_UNIFORM = {
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		static void setupMatrix(float x, float y, float w, float h, float winW, float winH, float rotZ = 0);
	};

	void IDrawable::setupMatrix(float x, float y, float w, float h, float winW, float winH, float rotZ)
	{
		MATRIX_UNIFORM.m41 = (2 * x / winW) - 1 + w / winW;
		MATRIX_UNIFORM.m42 = 1 - (2 * y / winH) - h / winH;
		if (rotZ != 0) {
			float cosZ = std::cos(rotZ);
			float sinZ = std::sin(rotZ);

			MATRIX_UNIFORM.m11 = (w / winW * 2) * cosZ;
			MATRIX_UNIFORM.m12 = -(w / winW * 2) * sinZ;
			MATRIX_UNIFORM.m21 = (h / winH * 2) * sinZ;
			MATRIX_UNIFORM.m22 = (h / winH * 2) * cosZ;
		}
		else {
			MATRIX_UNIFORM.m11 = w / winW * 2;
			MATRIX_UNIFORM.m12 = 0;
			MATRIX_UNIFORM.m21 = 0;
			MATRIX_UNIFORM.m22 = h / winH * 2;
		}
	}
}