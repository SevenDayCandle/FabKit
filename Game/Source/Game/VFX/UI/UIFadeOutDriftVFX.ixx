export module fbc.UIFadeOutDriftVFX;

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
	export class UIFadeOutDriftVFX : public VFX {
	public:
		UIFadeOutDriftVFX(FWindow& win, uptr<UIImage>&& image, float tOffX = 0, float tOffY = 0, float duration = DEFAULT_DURATION * 0.5f): VFX(win, duration), image(move(image)), tOffX(tOffX), tOffY(tOffY) {}

		inline UIFadeOutDriftVFX& setTOff(float tOffX, float tOffY) { return this->tOffX = tOffX, this->tOffY = tOffY, *this; }
		inline UIFadeOutDriftVFX& setTOffX(float tOffX) { return this->tOffX = tOffX, *this; }
		inline UIFadeOutDriftVFX& setTOffY(float tOffY) { return this->tOffY = tOffY, *this; }

		float tOffX;
		float tOffY;
		uptr<UIImage> image;

		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeOutDriftVFX::render(sdl::SDLBatchRenderPass& rp)
	{
		image->renderImpl(rp);
	}

	void UIFadeOutDriftVFX::update()
	{
		image->color.a = (duration - ticks) / duration;
		image->setHbOffsetPos(image->hb->getOffPosX() + tOffX, image->hb->getOffPosY() + tOffY);
	}
}