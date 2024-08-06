export module fbc.UIFadeInVFX;

import fbc.FUtil;
import fbc.UIImage;
import fbc.VFX;
import sdl;
import std;

namespace fbc {
	export class UIFadeInVFX : public VFX {
	public:
		UIFadeInVFX(uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f) : VFX(duration), image(move(image)) {}

		uptr<UIImage> image;

		virtual void render() override;
		virtual void update() override;
	private:
		float rate;
	};

	void UIFadeInVFX::render()
	{
		image->renderImpl();
	}

	void UIFadeInVFX::update()
	{
		image->color.a = 255 * ticks / duration;
	}
}