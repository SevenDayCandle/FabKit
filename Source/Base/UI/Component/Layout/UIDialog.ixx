export module fab.UIDialog;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;

import fab.UICanvas;
import fab.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UIDialog : public UICanvas<> {
	public:
		UIDialog(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UICanvas(window, move(hb)), image(image) {}

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
		image.draw(rp, *hb.get(), win.getW(), win.getH(), 1, 1);
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