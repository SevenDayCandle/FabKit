export module fab.FTexture;

import fab.FTextureBlock;
import fab.FUtil;
import fab.IDrawable;
import fab.BatchRenderPass;
import sdl.SDLBase;
import sdl.SDLRunner;
import std;

/* A wrapper around SDL's GPUTexture that handles disposal as well as basic rendering logic */
namespace fab {
	export class FTexture : public IDrawable, public FTextureBlock::Item {
	public:
		FTexture(FTextureBlock& source, strv path): FTextureBlock::Item(source), path(path) {}
		FTexture(const FTexture&) = delete;
		FTexture(FTexture&& other) noexcept : FTextureBlock::Item(move(other)), path(other.path) {}
		~FTexture() override {}

		str path;

		inline float getHeight() const override { return source.getHeight(); }
		inline float getWidth() const override { return source.getWidth(); }
		inline void dispose() override { release(); }

		void reload() const override;
		void reload(sdl::GPUCopyPass* copyPass) const override;
		void reload(sdl::GPUCopyPass* copyPass, sdl::Surface* surface) const;
	protected:
		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	};

	void FTexture::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		float sX = scX * w;
		float sY = scY * h;
		rp.bindPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.bindTexture(source);
		rp.pushVertexData({
			.texInd = index,
			.coord = BatchRenderPass::makeCoord(0, 0, 1, 1),
			.color = *tint,
			.transform = BatchRenderPass::makeTransform(tX, tY, sX, sY, rotZ)
		});
	}

	void FTexture::reload() const {
		sdl::GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
		reload(copyPass);
		sdl::gpuEndCopyPass(copyPass);
		sdl::gpuSubmit(uploadCmdBuf);
	}

	void FTexture::reload(sdl::GPUCopyPass* copyPass) const {
		sdl::Surface* surface = sdl::surfaceLoad(path.data());
		reload(copyPass, surface);
	}

	void FTexture::reload(sdl::GPUCopyPass* copyPass, sdl::Surface* surface) const {
		if (surface) {
			reupload(copyPass, surface);
			sdl::surfaceDestroy(surface);
		}
		else {
			release();
			sdl::logError("Failed to load texture %s: %s", path.c_str(), sdl::getError());
		}
	}
}
