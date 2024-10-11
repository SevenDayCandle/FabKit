export module fab.UIRecolorVFX;

import fab.CallbackVFX;
import fab.FUtil;
import fab.FWindow;
import fab.Hoverable;
import fab.UIImage;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UIRecolorVFX : public CallbackVFX {
	public:
		UIRecolorVFX(FWindow& window, UIImage& image, float srcR, float srcG, float srcB, float targR, float targG, float targB, float duration = DEFAULT_DURATION * 0.25f) : CallbackVFX(window, duration), image(image), targR(targR), targG(targG), targB(targB), srcR(srcR), srcG(srcG), srcB(srcB), token(image.makeToken()) {}
		UIRecolorVFX(FWindow& window, UIImage& image, const sdl::Color& srcColor, const sdl::Color& targColor, float duration = DEFAULT_DURATION * 0.25f) : UIRecolorVFX(window, image, srcColor.r, srcColor.g, srcColor.b, targColor.r, targColor.g, targColor.b, duration) {}
		UIRecolorVFX(FWindow& window, UIImage& image, const sdl::Color& color, float duration = DEFAULT_DURATION * 0.25f) : UIRecolorVFX(window, image, image.color.r, image.color.g, image.color.b, color.r, color.g, color.b, duration) {}
		virtual ~UIRecolorVFX() = default;

		UIImage& image;

		inline virtual void render(sdl::SDLBatchRenderPass& rp) override {}

		virtual void dispose() override;
		virtual bool tickUpdate() override;
		virtual void update() override;
	protected:
		float srcR;
		float srcG;
		float srcB;
		float targR;
		float targG;
		float targB;
	private:
		float interpHue;
		Hoverable::Token token;
	};

	void UIRecolorVFX::dispose() {
		image.color.r = targR;
		image.color.g = targG;
		image.color.b = targB;
		CallbackVFX::dispose();
	}

	bool UIRecolorVFX::tickUpdate() {
		if (!token) {
			dispose();
			return true;
		}
		return CallbackVFX::tickUpdate();
	}

	void UIRecolorVFX::update() {
		float rate = 1 - std::pow(1 - ticks / duration, 3);
		image.color.r = futil::fastLerp(srcR, targR, rate);
		image.color.g = futil::fastLerp(srcG, targG, rate);
		image.color.b = futil::fastLerp(srcB, targB, rate);
	}
}