export module fbc.UIScreen;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import fbc.ScreenSizeHitbox;
import fbc.UICanvas;
import std;

namespace fbc {
	export class UIScreen : public UICanvas {
	public:
		UIScreen() : UICanvas(new ScreenSizeHitbox()) {}
		UIScreen(Hitbox* hb) : UICanvas(hb) {}
		UIScreen(uptr<Hitbox>&& hb) : UICanvas(std::move(hb)) {}

		virtual UIScreen& addVFX(uptr<IOverlay>&& eff) override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	private:
		vec<uptr<IOverlay>> vfx;
	};

	UIScreen& UIScreen::addVFX(uptr<IOverlay>&& eff)
	{
		vfx.push_back(std::move(eff));
		return *this;
	}

	void UIScreen::renderImpl()
	{
		UICanvas::renderImpl();
		for (uptr<IOverlay>& effect : vfx) {
			effect->render();
		}
	}

	void UIScreen::updateImpl()
	{
		UICanvas::updateImpl();
		std::erase_if(vfx, [](uptr<IOverlay>& effect) {return effect->tickUpdate();});
	}
}