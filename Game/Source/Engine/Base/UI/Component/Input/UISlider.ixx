export module fbc.UISlider;

import fbc.CoreContent;
import fbc.IDrawable;
import fbc.UIHorizontalScrollbar;
import fbc.UINumberInput;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import sdl;
import std;

export namespace fbc {
	export class UISlider : public UINumberInput {
	public:
		UISlider(Hitbox* hb, Hitbox* scrollhb, IDrawable& imageBar = cct.images.sliderEmpty, IDrawable& imageButton = cct.images.scrollbutton): 
			UINumberInput(hb), scrollbar(scrollhb, imageBar, imageButton) {
			scrollbar.setOnScroll([this](float scroll) {this->commitFromScroll(scroll); });
		}
		UISlider(Hitbox* hb, IDrawable& imageBar = cct.images.sliderEmpty, IDrawable& imageButton = cct.images.scrollbutton) : 
			UISlider(hb, new RelativeHitbox(*hb, hb->getOffsetSizeX(), 0, hb->getOffsetSizeX() * 3, hb->getOffsetSizeY()), imageBar, imageButton) {}

		virtual ~UISlider() {}

		virtual void commit(int num) override;
		virtual void onSizeUpdated() override;
		virtual void refreshHb() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		UIHorizontalScrollbar scrollbar;
	private:
		void commitFromScroll(float scroll);
	};

	void UISlider::commit(int num)
	{
		UINumberInput::commit(num);
		float pos = limMin == limMax ? 0 : (num - limMin) / (limMax - limMin);
		scrollbar.setScrollPos(pos);
	}

	void UISlider::onSizeUpdated()
	{
		UINumberInput::onSizeUpdated();
		scrollbar.onSizeUpdated();
	}

	void UISlider::refreshHb()
	{
		UINumberInput::refreshHb();
		scrollbar.refreshHb();
	}

	void UISlider::renderImpl()
	{
		UINumberInput::renderImpl();
		scrollbar.renderImpl();
	}

	void UISlider::updateImpl()
	{
		UINumberInput::updateImpl();
		scrollbar.updateImpl();
	}

	void UISlider::commitFromScroll(float scroll)
	{
		int value = std::lerp(limMin, limMax, scroll);
		UINumberInput::commit(value);
	}
}