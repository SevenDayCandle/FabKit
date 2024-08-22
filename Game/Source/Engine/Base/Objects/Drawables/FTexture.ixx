export module fbc.FTexture;

import fbc.FUtil;
import fbc.ImageDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class FTexture : public ImageDrawable {
    public:
        FTexture(strv path) : path(path) {}
        FTexture(const FTexture&) = delete;
        FTexture(FTexture&& other) noexcept = default;

        void reload() const override;
        void reload(sdl::GpuCopyPass* copyPass) const;
        str path;
	};

    void FTexture::reload() const
    {
        sdl::GpuCommandBuffer* uploadCmdBuf = sdl::runner::deviceAcquireCommandBuffer();
        sdl::GpuCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
        reload(copyPass);
        sdl::gpuEndCopyPass(copyPass);
        sdl::gpuSubmit(uploadCmdBuf);
    }

    void FTexture::reload(sdl::GpuCopyPass* copyPass) const {
        if (texture) {
            sdl::runner::deviceReleaseTexture(texture);
        }
        sdl::Surface* surface = sdl::surfaceLoad(path.data());
        texH = surface->h;
        texW = surface->w;
        texture = sdl::runner::uploadTexture(copyPass, surface);

        sdl::surfaceDestroy(surface);
    }
}
