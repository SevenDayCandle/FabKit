export module fbc.UIDialog;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.ScreenManager;
import fbc.UICanvas;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class UIDialog : public UICanvas {
	public:
		UIDialog(Hitbox* hb, IDrawable& image) : UICanvas(hb), image(image) {}

		IDrawable& image;

		virtual bool isHovered() override;
		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
		virtual void updateImpl() override;
	};

	bool UIDialog::isHovered()
	{
		return hb->isHovered();
	}

	void UIDialog::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) {
		image.draw(hb.get());
		UICanvas::renderImpl(cd, rp);
	}

	void UIDialog::updateImpl()
	{
		UICanvas::updateImpl();
		if (sdl::mouseIsLeftJustClicked() && !isHovered()) {
			screenManager::closeOverlay(this);
		}
	}
}