export module fbc.FTexture;

import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import std;

namespace fbc {
	export class FTexture : public IDrawable {
    public:
        FTexture(strv path) : path(path) {}
        FTexture(const FTexture&) = delete;
        virtual ~FTexture() override {
            // Unload texture when destroyed
            if (texture && sdl::sdlEnabled()) {
                sdl::gpuReleaseTexture(texture);
                texture = nullptr;
            }
        }

        inline bool loaded() const { return texture != nullptr; }
        inline float getHeight() const override { return h; }
        inline float getWidth() const override { return w; }

        void dispose() override;
        void draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline) override;
        void reload() const override;
        void reload(sdl::GpuCopyPass* copyPass) const;
    protected:
        mutable float h;
        mutable float w;
        mutable sdl::GpuTexture* texture;
        str path;
	};

    void FTexture::dispose()
    {
        sdl::gpuReleaseTexture(texture);
        texture = nullptr;
    }

    void FTexture::draw(sdl::GpuCommandBuffer* cb, sdl::GpuRenderPass* rp, const sdl::Color* tint, float x, float y, float w, float h, float rotation, sdl::GpuGraphicsPipeline* pipeline)
    {
        sdl::queueDraw(cb, rp, texture, tint, x, y, w, h, rotation, pipeline);
    }

    void FTexture::reload() const
    {
        sdl::GpuCommandBuffer* uploadCmdBuf = sdl::gpuAcquireCommandBuffer();
        sdl::GpuCopyPass* copyPass = sdl::gpuBeginCopyPass(uploadCmdBuf);
        reload(copyPass);
        sdl::gpuEndCopyPass(copyPass);
        sdl::gpuSubmit(uploadCmdBuf);
    }

    void FTexture::reload(sdl::GpuCopyPass* copyPass) const {
        if (texture) {
            sdl::gpuReleaseTexture(texture);
        }
        sdl::Surface* surface = sdl::surfaceLoad(path.data());
        h = surface->h;
        w = surface->w;
        texture = sdl::uploadTexture(copyPass, surface);

        sdl::surfaceDestroy(surface);
    }
}
