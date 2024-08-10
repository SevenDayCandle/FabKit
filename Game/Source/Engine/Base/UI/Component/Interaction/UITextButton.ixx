export module fbc.UITextButton;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.TextInfo;
import fbc.UIButton;

namespace fbc {
	export class UITextButton : public UIButton, public TextInfo {
	public:
		UITextButton(Hitbox* hb, IDrawable& image, FFont& f, strv text = "") : UIButton(hb, image), TextInfo(f, text) {
			UITextButton::onSizeUpdated();
		}
		UITextButton(Hitbox* hb, strv text) : UITextButton(hb, cct.images.panel, cct.fontRegular(), text) {}
		~UITextButton() override {}

		virtual void onSizeUpdated() override;
		virtual void refreshDimensions() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
	};

	void UITextButton::onSizeUpdated()
	{
		TextInfo::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::refreshDimensions()
	{
		UIButton::refreshDimensions();
		refreshCache();
		TextInfo::setPos((this->hb->w - getTextWidth()) / 2, (this->hb->h - getTextHeight()) / 2);
	}

	void UITextButton::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		UIButton::renderImpl(cd, rp);
		TextInfo::drawText(hb->x, hb->y);
	}
}
