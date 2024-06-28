export module fbc.UIScreen;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import fbc.UICanvas;
import std;

namespace fbc {
	export class UIScreen : public UICanvas {
	public:
		UIScreen(Hitbox* hb) : UICanvas(hb) {}
		UIScreen(uptr<Hitbox>&& hb) : UICanvas(std::move(hb)) {}
		virtual ~UIScreen() {}

		virtual UIScreen& addVFX(uptr<IOverlay>&& eff) override;
		virtual void render() override;
		virtual void update() override;
	private:
		vec<uptr<IOverlay>> vfx;
	};

	UIScreen& UIScreen::addVFX(uptr<IOverlay>&& eff)
	{
		vfx.push_back(std::move(eff));
		return *this;
	}

	void UIScreen::render()
	{
		UICanvas::render();
		for (uptr<IOverlay>& effect : vfx) {
			effect->render();
		}
	}

	void UIScreen::update()
	{
		UICanvas::update();
		std::erase_if(vfx, [](uptr<IOverlay>& effect) {return effect->tickUpdate();});
	}
}