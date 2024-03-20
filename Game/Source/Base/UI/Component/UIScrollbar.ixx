export module fbc.UIScrollbar;

import fbc.uiHoverable;
import fbc.futil;

export namespace fbc {
	export class UIScrollbar : public UIHoverable {
	public:
		UIScrollbar(Hitbox* hb): UIHoverable(hb) {}
		virtual ~UIScrollbar() {}

		inline UIScrollbar& setOnScroll(const func<void(float)>& onScroll) { return this->onScroll = onScroll, *this; }

		virtual void renderImpl() override;
		virtual void updateImpl() override;

		float fromPercentage(float percent);
		virtual float toPercentage(float x, float y);
	private:
		float scrollPercent;
		func<void(float)> onScroll;
	};

	void UIScrollbar::renderImpl() {
		// TODO highlight if hovered
	}

	void UIScrollbar::updateImpl() {
		UIHoverable::updateImpl();


	}
}