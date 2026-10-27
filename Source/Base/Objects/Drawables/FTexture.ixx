module;

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

export module fab.FTexture;

import fab.FTextureBlock;
import fab.FUtil;
import fab.IDrawable;
import fab.BatchRenderPass;
import sdl.SDLHelpers;
import sdl.SDLRunner;
import std;

/* A wrapper around SDL's GPUTexture that handles disposal as well as basic rendering logic */
namespace fab {
	export class FTexture : public IDrawable, public FTextureBlock::Item {
	public:
		FTexture(FTextureBlock& source, strv path) : FTextureBlock::Item(source), path(path) {}
		FTexture(const FTexture&) = delete;
		FTexture(FTexture&& other) noexcept : FTextureBlock::Item(move(other)), path(other.path) {}
		~FTexture() override { release(); }

		inline float getHeight() const override { return source.getHeight(); }
		inline float getWidth() const override { return source.getWidth(); }
		inline void dispose() override { release(); }

		void reload() const override;
		void reload(::SDL_GPUCopyPass* copyPass) const override;
		void reload(::SDL_GPUCopyPass* copyPass, sdl::Surface* surface) const;
	protected:
		str path;

		void drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) override;
	};

	void FTexture::drawCentered(BatchRenderPass& rp, float tX, float tY, float w, float h, float scX, float scY, float rotZ, const sdl::Color* tint, sdl::RenderMode pipeline) {
		float sX = scX * w;
		float sY = scY * h;
		rp.setPipeline(sdl::runner::pipelineForMode(pipeline));
		rp.setTexture(source);
		rp.pushVertexData({
			.transform = BatchRenderPass::makeTransform(tX, tY, sX, sY, rotZ),
			.color = *tint,
			.coord = BatchRenderPass::makeCoord(0, 0, 1, 1),
			.texInd = static_cast<float>(index),
		});
	}

	void FTexture::reload() const {
		::SDL_GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
		::SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);
		reload(copyPass);
		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(uploadCmdBuf);
	}

	void FTexture::reload(::SDL_GPUCopyPass* copyPass) const {
		sdl::Surface* surface = IMG_Load(path.data());
		reload(copyPass, surface);
	}

	void FTexture::reload(::SDL_GPUCopyPass* copyPass, sdl::Surface* surface) const {
		if (surface) {
			reupload(copyPass, surface);
			SDL_DestroySurface(surface);
		}
		else {
			sdl::logError("Failed to load texture %s: %s", path.c_str(), sdl::getError());
			release();
		}
	}
}
