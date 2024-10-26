export module fab.UITranslateVFX;

import fab.CallbackVFX;
import fab.FUtil;
import fab.FWindow;
import fab.Hoverable;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UITranslateVFX : public CallbackVFX {
	public:
		UITranslateVFX(FWindow& window, Hoverable& image, float duration = 0.5f) : CallbackVFX(window, duration), ui(image), token(image.makeToken()), posXBegin(image.getHb()->x), posXEnd(image.getHb()->x), posYBegin(image.getHb()->y), posYEnd(image.getHb()->y) {}
		virtual ~UITranslateVFX() = default;

		Hoverable& ui;

		inline UITranslateVFX& setInterpClampExp(float ratio, float n) { return this->interpFunc = [n, ratio](float t, float d) {return VFX::clampExp(t, d * ratio, n); }, *this; }
		inline UITranslateVFX& setInterpCubic() { return this->interpFunc = [](float t, float d) {return VFX::exp(t, d, 3); }, *this; }
		inline UITranslateVFX& setInterpExp(float n) { return this->interpFunc = [n](float t, float d) {return VFX::exp(t, d, n); }, *this; }
		inline UITranslateVFX& setInterpFunc(const func<float(float, float)>& lerpFunc) { return this->interpFunc = lerpFunc, *this; }
		inline UITranslateVFX& setMoveByOffset(float tOffX, float tOffY) {
			return setMove(ui.getHb()->toRealPosX(tOffX), ui.getHb()->toRealPosY(tOffY));
		}
		inline UITranslateVFX& setMoveRelative(float x, float y) {
			return setMove(ui.getHb()->x + x, ui.getHb()->y + y);
		}
		inline virtual void render(sdl::SDLBatchRenderPass& rp) override {}

		UITranslateVFX& setMove(float x, float y);
		virtual void dispose() override;
		virtual bool tickUpdate() override;
		virtual void update() override;
	protected:
		float posXBegin;
		float posXEnd;
		float posYBegin;
		float posYEnd;
		func<float(float, float)> interpFunc = VFX::linear;
	private:
		Hoverable::Token token;
	};

	UITranslateVFX& UITranslateVFX::setMove(float x, float y) {
		posXEnd = x;
		posYEnd = y;
		return *this;
	}

	void UITranslateVFX::dispose() {
		ui.getHb()->setRealPos(posXEnd, posYEnd);
		CallbackVFX::dispose();
	}

	bool UITranslateVFX::tickUpdate() {
		if (!token) {
			dispose();
			return true;
		}
		return CallbackVFX::tickUpdate();
	}

	void UITranslateVFX::update() {
		float rate = interpFunc(ticks, duration);
		ui.getHb()->setRealPos(futil::fastLerp(posXBegin, posXEnd, rate), futil::fastLerp(posYBegin, posYEnd, rate));
	}
}