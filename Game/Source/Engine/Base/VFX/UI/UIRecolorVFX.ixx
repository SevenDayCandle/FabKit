export module fbc.UIRecolorVFX;

import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hoverable;
import fbc.UIImage;
import fbc.VFX;
import sdl.HSVTuple;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIRecolorVFX : public CallbackVFX {
	public:
		UIRecolorVFX(FWindow& window, UIImage& image, float r, float g, float b, float duration = DEFAULT_DURATION * 0.5f) : CallbackVFX(window, duration), image(image), targHSV(sdl::HSVTuple::toHSV(r, g, b)), srcHSV(sdl::HSVTuple::toHSV(image.color)), token(image.makeToken()) {
			refreshInterpHue();
		}
		UIRecolorVFX(FWindow& window, UIImage& image, const sdl::Color& color, float duration = DEFAULT_DURATION * 0.5f) : UIRecolorVFX(window, image, color.r, color.g, color.b, duration) {}
		virtual ~UIRecolorVFX() = default;

		UIImage& image;

		virtual void dispose() override;
		virtual bool tickUpdate() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void update() override;
	protected:
		sdl::HSVTuple srcHSV;
		sdl::HSVTuple targHSV;
	private:
		float interpHue;
		Hoverable::Token token;

		void refreshInterpHue();
	};

	void UIRecolorVFX::dispose() {
		sdl::HSVTuple::fromHSV(targHSV, image.color);
		CallbackVFX::dispose();
	}

	bool UIRecolorVFX::tickUpdate() {
		if (!token) {
			dispose();
			return true;
		}
		return CallbackVFX::tickUpdate();
	}

	void UIRecolorVFX::render(sdl::SDLBatchRenderPass& rp) {
		image.renderImpl(rp);
	}

	void UIRecolorVFX::update() {
		float rate = 1 - std::pow(1 - ticks / duration, 3);
		sdl::HSVTuple tuple = {
			.h = srcHSV.h + rate * interpHue,
			.s = futil::fastLerp(srcHSV.s, targHSV.s, rate),
			.v = futil::fastLerp(srcHSV.v, targHSV.v, rate),
		};
		sdl::HSVTuple::fromHSV(tuple, image.color);
	}

	// When interpolating hue, we want to interpolate across the direction that is shorter
	// If we are interpolating to or from a color with a saturation of 0, we should not change the hue to make transitions smoother
	void UIRecolorVFX::refreshInterpHue() {
		if (targHSV.s <= 0) {
			targHSV.h = srcHSV.h;
			interpHue = 0;
		}
		else if (srcHSV.s <= 0) {
			srcHSV.h = targHSV.h;
			interpHue = 0;
		}
		else {
			interpHue = targHSV.h - srcHSV.h;
			if (interpHue > 0.5) {
				interpHue -= 1.0;
			}
			else if (interpHue < -0.5) {
				interpHue += 1.0;
			}
		}
	}
}