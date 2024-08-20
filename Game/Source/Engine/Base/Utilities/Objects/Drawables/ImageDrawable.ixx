export module fbc.ImageDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
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
		inline virtual float getHeight() const override { return texH; }
		inline virtual float getWidth() const override { return texW; }
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override { draw(rp, sdl::runner::BUFFER_VERTEX, x, y, w, h, winW, winH, rotZ, tint, pipeline, 0); }

		void dispose() override;
		void draw(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float x, float y, float w, float h, float winW, float winH, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL, int vertexOff = 0);
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

	void ImageDrawable::draw(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float x, float y, float w, float h, float winW, float winH, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline, int vertexOff)
	{
		setupMatrix(x, y, w, h, winW, winH, rotZ);
		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(bufferVert);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushVertexUniform(&MATRIX_UNIFORM, sizeof(sdl::Matrix4x4));
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives(vertexOff);
	}
}