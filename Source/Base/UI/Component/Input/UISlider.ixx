export module fab.UISlider;

import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.RelativeHitbox;
import fab.UIHorizontalScrollbar;
import fab.UINumberInput;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UISlider : public UINumberInput {
	public:
		UISlider(FWindow& window, uptr<Hitbox>&& hb, uptr<Hitbox>&& scrollhb, int limMin, int limMax,
			IDrawable& imageBar, IDrawable& imageButton, IDrawable& panelImage) :
			UINumberInput(window, move(hb), limMin, limMax, panelImage),
			scrollbar(window, move(scrollhb), imageBar, imageButton) {
			scrollbar.setOnScroll([this](float scroll) { this->commitFromScroll(scroll); });
		}
		UISlider(FWindow& window, uptr<Hitbox>&& hb, int limMin, int limMax,
			IDrawable& imageBar, IDrawable& imageButton, IDrawable& panelImage) :
			UISlider(window, move(hb), std::make_unique<RelativeHitbox>(window, *hb, hb->getOffSizeX() + 4, 0, hb->getOffSizeX() * 3, hb->getOffSizeY()),
				limMin, limMax, imageBar, imageButton, panelImage) {}
		UISlider(FWindow& window, uptr<Hitbox>&& hb, uptr<Hitbox>&& scrollhb, int limMin = 0, int limMax = std::numeric_limits<int>::max()) :
			UISlider(window, move(hb), move(scrollhb), limMin, limMax,
				window.props.defaultSlider(), window.props.defaultScrollButton(), window.props.defaultPanel()) {}
		UISlider(FWindow& window, uptr<Hitbox>&& hb, int limMin = 0, int limMax = std::numeric_limits<int>::max()) :
			UISlider(window, move(hb), limMin, limMax,
				window.props.defaultSlider(), window.props.defaultScrollButton(), window.props.defaultPanel()) {}
		UISlider(UISlider&& other) noexcept: UINumberInput(other.win, move(other.hb), other.limMin, other.limMax, *other.image), scrollbar(std::move(other.scrollbar)) {
			scrollbar.setOnScroll([this](float scroll) { this->commitFromScroll(scroll); });
		}

		virtual UISlider& setValue(int num) override;
		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(BatchRenderPass& rp) override;
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

	void UISlider::renderImpl(BatchRenderPass& rp)
	{
		UINumberInput::renderImpl(rp);
		scrollbar.renderImpl(rp);
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