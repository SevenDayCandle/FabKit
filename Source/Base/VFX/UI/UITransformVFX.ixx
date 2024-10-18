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
		virtual ~UITransformVFX() = default;

		UIImage& image;
		
		inline UITransformVFX& setLerpCubic() { return this->lerpFunc = VFX::cubic, *this; }
		inline UITransformVFX& setLerpFunc(const func<float(float, float)>& lerpFunc) { return this->lerpFunc = lerpFunc, *this; }
		inline UITransformVFX& setMoveRelative(float tOffX, float tOffY) { 
			return setMove(image.hb->getOffPosX() + tOffX, image.hb->getOffPosY() + tOffY);
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
		UITransformVFX& setMove(float tOffX, float tOffY);
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
			image(image), token(image.makeToken()), alphaBegin(image.color.a), alphaEnd(alphaEnd), posXBegin(image.hb->getOffPosX()), posXEnd(image.hb->getOffPosX()),
			posYBegin(image.hb->getOffPosY()), posYEnd(image.hb->getOffPosY()), rotBegin(image.rotation), rotEnd(image.rotation), scaleXBegin(image.scaleX), scaleXEnd(image.scaleX), scaleYBegin(image.scaleY), scaleYEnd(image.scaleY) {}

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
		func<float(float, float)> lerpFunc = VFX::linear;
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

	UITransformVFX& UITransformVFX::setMove(float tOffX, float tOffY) {
		posXEnd = tOffX;
		posYEnd = tOffY;
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
			image.hb->setOffPos(posXEnd, posYEnd);
		}
		CallbackVFX::dispose();
	}

	bool UITransformVFX::tickUpdate() {
		if (!token) {
			dispose();
			return true;
		}
		return CallbackVFX::tickUpdate();
	}

	void UITransformVFX::update() {
		float rate = lerpFunc(ticks, duration);
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
			image.hb->setOffPos(futil::fastLerp(posXBegin, posXEnd, rate), futil::fastLerp(posYBegin, posYEnd, rate));
		}
	}
}