export module fbc.ImageDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class ImageDrawable : public IDrawable {
	public:
		ImageDrawable() {}
		ImageDrawable(const ImageDrawable&) = delete;
		ImageDrawable(ImageDrawable&& other) noexcept : texH(other.texH), texW(other.texW), texture(other.texture) {
			other.texture = nullptr;
		}
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
		inline void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override { 
			drawImpl(rp, sdl::runner::BUFFER_VERTEX, (x + (0.5f * scX * w)) / winW, (y + (0.5f * scY * h)) / winH, scX * w / winW, scY * h / winH, rotZ, tint, pipeline, 0);
		}

		void dispose() override;
	protected:
		mutable float texH = 0;
		mutable float texW = 0;
		mutable sdl::GpuTexture* texture = nullptr;

		void drawImpl(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float tX, float tY, float sX, float sY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL, int vertexOff = 0);
	};

	void ImageDrawable::dispose()
	{
		sdl::runner::deviceReleaseTexture(texture);
		texture = nullptr;
	}

	void ImageDrawable::drawImpl(sdl::SDLBatchRenderPass& rp, sdl::GpuBuffer* bufferVert, float tX, float tY, float sX, float sY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline, int vertexOff)
	{
		setupMatrix(tX, tY, sX, sY, rotZ);
		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(bufferVert);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.pushVertexUniform(&MATRIX_UNIFORM, sizeof(sdl::Matrix4x4));
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives(vertexOff);
	}
}
