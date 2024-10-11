export module fbc.ImageDrawable;

import fbc.FUtil;
import fbc.IDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
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
		ImageDrawable(float w, float h, sdl::GPUTexture* texture): texH(h), texW(w), texture(texture) {}
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
		inline virtual void draw(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) override {
			drawImpl(rp, (x + (0.5f * w)) / winW, (y + (0.5f * h)) / winH, scX * w / winW, scY * h / winH, rotZ, tint, pipeline);
		}
		inline virtual void drawCentered(sdl::SDLBatchRenderPass& rp, float x, float y, float w, float h, float winW, float winH, float scX, float scY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL) {
			drawImpl(rp, x / winW, y / winH, scX * w / winW, scY * h / winH, rotZ, tint, pipeline);
		}

		void dispose() override;
	protected:
		mutable float texH = 0;
		mutable float texW = 0;
		mutable sdl::GPUTexture* texture = nullptr;

		void drawImpl(sdl::SDLBatchRenderPass& rp, float tX, float tY, float sX, float sY, float rotZ = 0, const sdl::Color* tint = &sdl::COLOR_STANDARD, sdl::RenderMode pipeline = sdl::RenderMode::NORMAL);
	};

	void ImageDrawable::dispose()
	{
		sdl::runner::deviceReleaseTexture(texture);
		texture = nullptr;
	}

	void ImageDrawable::drawImpl(sdl::SDLBatchRenderPass& rp, float tX, float tY, float sX, float sY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline)
	{
		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindBufferVertex(sdl::runner::BUFFER_VERTEX);
		rp.bindBufferIndex(sdl::runner::BUFFER_INDEX);
		rp.bindTexture(texture, sdl::runner::SAMPLER);
		rp.setupVertexUniform(tX, tY, sX, sY, rotZ);
		rp.pushFragmentUniform(tint, sizeof(sdl::Color));
		rp.drawIndexedPrimitives();
	}
}
