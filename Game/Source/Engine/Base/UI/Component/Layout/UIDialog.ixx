export module fbc.UIDialog;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.IDrawable;

import fbc.UICanvas;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIDialog : public UICanvas {
	public:
		UIDialog(FWindow& window, Hitbox* hb, IDrawable& image) : UICanvas(window, hb), image(image) {}

		IDrawable& image;

		virtual bool isHovered() override;
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	};

	bool UIDialog::isHovered()
	{
		return hb->isHovered();
	}

	void UIDialog::renderImpl(sdl::SDLBatchRenderPass& rp) {
		image.draw(rp, *hb.get(), win.getW(), win.getH());
		UICanvas::renderImpl(rp);
	}

	void UIDialog::updateImpl()
	{
		UICanvas::updateImpl();
		if (sdl::runner::mouseIsLeftJustClicked() && !isHovered()) {
			this->win.closeOverlay(this);
		}
	}
}