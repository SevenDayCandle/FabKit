export module fbc.ImageDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {
	export class ImageDrawable : public IDrawable {
	public:
		ImageDrawable() {}
		ImageDrawable(const ImageDrawable&) = delete;
		ImageDrawable(float w, float h, sdl::GpuTexture* texture): texH(h), texW(w), texture(texture) {}
		virtual ~ImageDrawable() override {
			if (texture && sdl::runner::enabled()) {
				sdl::runner::deviceReleaseTexture(texture);
				texture = nullptr;
			}
		}

		operator bool() const { return texture != nullptr; }

		inline bool loaded() const { return texture != nullptr; }
		inline float getHeight() const override { return texH; }
		inline float getWidth() const override { return texW; }
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::GpuGraphicsPipeline* pipeline = sdl::runner::RENDER_STANDARD) override { draw(rp, sdl::runner::BUFFER_VERTEX, x, y, w, h, winW, winH, rotZ, tint, pipeline, 0); }

		void dispose() override;
		void draw(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::GpuGraphicsPipeline* pipeline, int vertexOff = 0);
	protected:
		mutable float texH;
		mutable float texW;
		mutable sdl::GpuTexture* texture;
	};

	void ImageDrawable::dispose()
	{
		sdl::runner::deviceReleaseTexture(texture);
		texture = nullptr;
	}

	void ImageDrawable::draw(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::GpuGraphicsPipeline* pipeline, int vertexOff)
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

		rp.bindPipeline(pipeline);
		rp.bindBufferVertex(bufferVert);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushVertexUniformAuto(&MATRIX_UNIFORM);
		rp.pushFragmentUniformAuto(tint);
		rp.drawIndexedPrimitives(vertexOff);
	}
}