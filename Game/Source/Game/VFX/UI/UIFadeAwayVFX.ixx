export module fbc.UIFadeAwayVFX;

import fbc.FUtil;
import fbc.UIImage;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class UIFadeAwayVFX : public VFX {
	public:
		UIFadeAwayVFX(uptr<UIImage>&& image, float duration = DEFAULT_DURATION): VFX(duration), image(move(image)) {}

		uptr<UIImage> image;

		virtual void render() override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeAwayVFX::render()
	{
		image->renderImpl();
	}

	void UIFadeAwayVFX::update()
	{
		if (duration > 0) {
			image->color.a = (duration - ticks) / duration;
		}
	}
}