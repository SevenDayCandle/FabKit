export module fab.FTexture;

import fab.FUtil;
import fab.ImageDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

/* Represents an image loaded from a file */
namespace fab {
	export class FTexture : public ImageDrawable {
    public:
        FTexture(strv path) : path(path) {}
        FTexture(const FTexture&) = delete;
        FTexture(FTexture&& other) noexcept = default;

        void reload() const override;
        void reload(sdl::GPUCopyPass* copyPass) const;
        str path;
	};

    void FTexture::reload() const
    {
        sdl::GPUCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
        sdl::GPUCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
        reload(copyPass);
        sdl::gpuEndCopyPass(copyPass);
        sdl::gpuSubmit(uploadCmdBuf);
    }

    void FTexture::reload(sdl::GPUCopyPass* copyPass) const {
        if (texture) {
            sdl::runner::deviceReleaseTexture(texture);
        }
        sdl::Surface* surface = sdl::surfaceLoad(path.data());
        if (surface) {
            texH = surface->h;
            texW = surface->w;
            texture = sdl::runner::uploadTexture(copyPass, surface);
            sdl::surfaceDestroy(surface);
        }
        else {
            texture = nullptr;
            sdl::logError("Failed to load texture %s: %s", path.c_str(), sdl::getError());
        }
    }
}
