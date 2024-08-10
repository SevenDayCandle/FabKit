export module fbc.UIFadeOutVFX;

import fbc.FUtil;
import fbc.UIImage;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class UIFadeOutVFX : public VFX {
	public:
		UIFadeOutVFX(uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f) : VFX(duration), image(move(image)) {}

		uptr<UIImage> image;

		virtual void render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeOutVFX::render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		image->renderImpl(cd, rp);
	}

	void UIFadeOutVFX::update()
	{
		image->color.a = (duration - ticks) / duration;
	}
}