export module fbc.UISlider;

import fbc.CoreContent;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.RelativeHitbox;
import fbc.UIHorizontalScrollbar;
import fbc.UINumberInput;
import sdl;
import std;

export namespace fbc {
	export class UISlider : public UINumberInput {
	public:
		UISlider(Hitbox* hb, Hitbox* scrollhb, int limMin = 0,
			int limMax = std::numeric_limits<int>::max(), IDrawable& imageBar = cct.images.sliderEmpty, IDrawable& imageButton = cct.images.scrollbutton, IDrawable& panelImage = cct.images.panel):
			UINumberInput(hb, limMin, limMax, panelImage), scrollbar(scrollhb, imageBar, imageButton) {
			scrollbar.setOnScroll([this](float scroll) {this->commitFromScroll(scroll); });
		}
		UISlider(Hitbox* hb, int limMin = 0,
			int limMax = std::numeric_limits<int>::max(),IDrawable& imageBar = cct.images.sliderEmpty, IDrawable& imageButton = cct.images.scrollbutton, IDrawable& panelImage = cct.images.panel) :
			UISlider(hb, new RelativeHitbox(*hb, hb->getOffsetSizeX() + 4, 0, hb->getOffsetSizeX() * 3, hb->getOffsetSizeY()), limMin, limMax, imageBar, imageButton, panelImage) {}

		virtual ~UISlider() {}

		virtual UISlider& setValue(int num) override;
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		UIHorizontalScrollbar scrollbar;

		void commitInternal() override;
	private:
		void commitFromScroll(float scroll);
	};

	void UISlider::onSizeUpdated()
	{
		UINumberInput::onSizeUpdated();
		scrollbar.onSizeUpdated();
	}

	void UISlider::refreshDimensions()
	{
		UINumberInput::refreshDimensions();
		scrollbar.refreshDimensions();
	}

	void UISlider::renderImpl()
	{
		UINumberInput::renderImpl();
		scrollbar.renderImpl();
	}

	UISlider& UISlider::setValue(int num)
	{
		UINumberInput::setValue(num);
		float pos = limMin == limMax ? 0 : (num - limMin) / static_cast<float>(limMax - limMin);
		scrollbar.setScrollPos(pos);
		return *this;
	}

	void UISlider::updateImpl()
	{
		UINumberInput::updateImpl();
		scrollbar.updateImpl();
	}

	void UISlider::commitInternal()
	{
		UINumberInput::commitInternal();
		float pos = limMin == limMax ? 0 : (getValue() - limMin) / static_cast<float>(limMax - limMin);
		scrollbar.setScrollPos(pos);
	}

	void UISlider::commitFromScroll(float scroll)
	{
		int value = std::lerp(limMin, limMax, scroll);
		UINumberInput::setValue(value);
		doOnComplete(value);
	}
}