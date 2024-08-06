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

		virtual void render() override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeOutVFX::render()
	{
		image->renderImpl();
	}

	void UIFadeOutVFX::update()
	{
		image->color.a = 255 * (duration - ticks) / duration;
	}
}