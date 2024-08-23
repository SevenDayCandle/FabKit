export module fbc.UIFadeInVFX;

import fbc.FUtil;
import fbc.FWindow;
import fbc.UIImage;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIFadeInVFX : public VFX {
	public:
		UIFadeInVFX(FWindow& window, uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f) : VFX(window, duration), image(move(image)) {}

		uptr<UIImage> image;

		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeInVFX::render(sdl::SDLBatchRenderPass& rp)
	{
		image->renderImpl(rp);
	}

	void UIFadeInVFX::update()
	{
		image->color.a = ticks / duration;
	}
}