export module fbc.UIFadeOutDriftVFX;

import fbc.FUtil;
import fbc.UIImage;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class UIFadeOutDriftVFX : public VFX {
	public:
		UIFadeOutDriftVFX(uptr<UIImage>&& image, float tOffX = 0, float tOffY = 0, float duration = DEFAULT_DURATION * 0.5f): VFX(duration), image(move(image)), tOffX(tOffX), tOffY(tOffY) {}

		inline UIFadeOutDriftVFX& setTOff(float tOffX, float tOffY) { return this->tOffX = tOffX, this->tOffY = tOffY, *this; }
		inline UIFadeOutDriftVFX& setTOffX(float tOffX) { return this->tOffX = tOffX, *this; }
		inline UIFadeOutDriftVFX& setTOffY(float tOffY) { return this->tOffY = tOffY, *this; }

		float tOffX;
		float tOffY;
		uptr<UIImage> image;

		virtual void render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeOutDriftVFX::render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		image->renderImpl(cd, rp);
	}

	void UIFadeOutDriftVFX::update()
	{
		image->color.a = (duration - ticks) / duration;
		image->setHbOffsetPos(image->hb->getOffPosX() + tOffX, image->hb->getOffPosY() + tOffY);
	}
}