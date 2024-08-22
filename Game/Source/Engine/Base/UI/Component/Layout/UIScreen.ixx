export module fbc.UIScreen;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.ScreenSizeHitbox;
import fbc.UICanvas;
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {
	export class UIScreen : public UICanvas {
	public:
		UIScreen(FWindow& window) : UICanvas(window, make_unique<ScreenSizeHitbox>(window)) {}
		UIScreen(FWindow& window, uptr<Hitbox>&& hb) : UICanvas(window, move(hb)) {}

		virtual UIScreen& addVFX(uptr<FWindow::Element>&& eff);
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
		virtual void updateImpl() override;
	private:
		vec<uptr<FWindow::Element>> vfx;
	};

	UIScreen& UIScreen::addVFX(uptr<FWindow::Element>&& eff)
	{
		vfx.push_back(std::move(eff));
		return *this;
	}

	void UIScreen::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UICanvas::renderImpl(rp);
		for (uptr<FWindow::Element>& effect : vfx) {
			effect->render(rp);
		}
	}

	void UIScreen::updateImpl()
	{
		UICanvas::updateImpl();
		std::erase_if(vfx, [](uptr<FWindow::Element>& effect) {return effect->tickUpdate();});
	}
}