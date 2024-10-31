export module fab.UITransformVFX;

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
	export class UITransformVFX : public CallbackVFX {
	public:
		UITransformVFX(FWindow& window, UIImage& image, float duration = 0.5f) : UITransformVFX(window, image, duration, image.color.a) {}
		UITransformVFX(UIImage& image, float duration = 0.5f) : UITransformVFX(image.win, image, duration, image.color.a) {}
		virtual ~UITransformVFX() = default;

		UIImage& image;
		
		inline UITransformVFX& setInterpClampExp(float ratio, float n) { return this->interpFunc = [n, ratio](float t, float d) {return VFX::clampExp(t, d * ratio, n); }, *this; }
		inline UITransformVFX& setInterpCubic() { return this->interpFunc = [](float t, float d) {return VFX::exp(t, d, 3); }, *this; }
		inline UITransformVFX& setInterpExp(float n) { return this->interpFunc = [n](float t, float d) {return VFX::exp(t, d, n); }, *this; }
		inline UITransformVFX& setInterpFunc(const func<float(float, float)>& lerpFunc) { return this->interpFunc = lerpFunc, *this; }
		inline UITransformVFX& setMoveByOffset(float tOffX, float tOffY) {
			return setMove(image.hb->toRealPosX(tOffX), image.hb->toRealPosY(tOffY));
		}
		inline UITransformVFX& setMoveRelative(float x, float y) { 
			return setMove(image.hb->x + x, image.hb->y + y);
		}
		inline UITransformVFX& setScale(float sEnd) {
			setScaleX(sEnd);
			return setScaleY(sEnd);
		}
		inline UITransformVFX& setScale(float sStart, float sEnd) {
			setScaleX(sStart, sEnd);
			return setScaleY(sStart, sEnd);
		}
		inline virtual void render(sdl::SDLBatchRenderPass& rp) override {}

		UITransformVFX& setFade(float aEnd);
		UITransformVFX& setFade(float aStart, float aEnd);
		UITransformVFX& setMove(float x, float y);
		UITransformVFX& setRotate(float rEnd);
		UITransformVFX& setRotate(float rStart, float rEnd);
		UITransformVFX& setScaleX(float sEnd);
		UITransformVFX& setScaleX(float sStart, float sEnd);
		UITransformVFX& setScaleY(float sEnd);
		UITransformVFX& setScaleY(float sStart, float sEnd);
		virtual void dispose() override;
		virtual bool tickUpdate() override;
		virtual void update() override;
	protected:
		UITransformVFX(FWindow& window, UIImage& image, float duration, float alphaEnd) : CallbackVFX(window, duration),
			image(image), token(image.makeToken()), alphaBegin(image.color.a), alphaEnd(alphaEnd), posXBegin(image.hb->x), posXEnd(image.hb->x),
			posYBegin(image.hb->y), posYEnd(image.hb->y), rotBegin(image.rotation), rotEnd(image.rotation), scaleXBegin(image.scaleX), scaleXEnd(image.scaleX), scaleYBegin(image.scaleY), scaleYEnd(image.scaleY) {}

		float alphaBegin;
		float alphaEnd;
		float posXBegin;
		float posXEnd;
		float posYBegin;
		float posYEnd;
		float rotBegin;
		float rotEnd;
		float scaleXBegin;
		float scaleXEnd;
		float scaleYBegin;
		float scaleYEnd;
		func<float(float, float)> interpFunc = VFX::linear;
	private:
		Hoverable::Token token;
	};

	UITransformVFX& UITransformVFX::setFade(float aEnd) {
		alphaEnd = aEnd;
		return *this;
	}

	UITransformVFX& UITransformVFX::setFade(float aStart, float aEnd) {
		image.color.a = alphaBegin = aStart;
		return setFade(aEnd);
	}

	// Set the target position to move the UI to. x/y are given as real coordinates
	UITransformVFX& UITransformVFX::setMove(float x, float y) {
		posXEnd = x;
		posYEnd = y;
		return *this;
	}

	UITransformVFX& UITransformVFX::setRotate(float rEnd) {
		rotEnd = rEnd;
		return *this;
	}

	UITransformVFX& UITransformVFX::setRotate(float rStart, float rEnd) {
		image.rotation = rotBegin = rStart;
		return setRotate(rEnd);
	}

	UITransformVFX& UITransformVFX::setScaleX(float sEnd) {
		scaleXEnd = sEnd;
		return *this;
	}

	UITransformVFX& UITransformVFX::setScaleX(float sStart, float sEnd) {
		image.scaleX = scaleXBegin = sStart;
		return setScaleX(sEnd);
	}


	UITransformVFX& UITransformVFX::setScaleY(float sEnd) {
		scaleYEnd = sEnd;
		return *this;
	}

	UITransformVFX& UITransformVFX::setScaleY(float sStart, float sEnd) {
		image.scaleY = scaleYBegin = sStart;
		return setScaleY(sEnd);
	}

	void UITransformVFX::dispose() {
		if (alphaBegin != alphaEnd) {
			image.color.a = alphaEnd;
		}
		if (rotBegin != rotEnd) {
			image.rotation = rotEnd;
		}
		if (scaleXBegin != scaleXEnd) {
			image.scaleX = scaleXEnd;
		}
		if (scaleYBegin != scaleYEnd) {
			image.scaleY = scaleYEnd;
		}
		if (posXBegin != posXEnd || posYBegin != posYEnd) {
			image.hb->setRealPos(posXEnd, posYEnd);
		}
		CallbackVFX::dispose();
	}

	bool UITransformVFX::tickUpdate() {
		if (!token) {
			CallbackVFX::dispose();
			return true;
		}
		return CallbackVFX::tickUpdate();
	}

	void UITransformVFX::update() {
		float rate = interpFunc(ticks, duration);
		if (alphaBegin != alphaEnd) {
			image.color.a = futil::fastLerp(alphaBegin, alphaEnd, rate);
		}
		if (scaleXBegin != scaleXEnd) {
			image.scaleX = futil::fastLerp(scaleXBegin, scaleXEnd, rate);
		}
		if (scaleYBegin != scaleYEnd) {
			image.scaleY = futil::fastLerp(scaleYBegin, scaleYEnd, rate);
		}
		if (rotBegin != rotEnd) {
			image.rotation = futil::fastLerp(rotBegin, rotEnd, rate);
		}
		if (posXBegin != posXEnd || posYBegin != posYEnd) {
			image.hb->setRealPos(futil::fastLerp(posXBegin, posXEnd, rate), futil::fastLerp(posYBegin, posYEnd, rate));
		}
	}
}