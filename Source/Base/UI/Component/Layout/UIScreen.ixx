export module fab.UIScreen;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.ScreenSizeHitbox;
import fab.UICanvas;
import fab.VFX;
import fab.BatchRenderPass;
import std;

namespace fab {
	export class UIScreen : public UICanvas<> {
	public:
		UIScreen(FWindow& window) : UICanvas(window, make_unique<ScreenSizeHitbox>(window)) {}
		UIScreen(FWindow& window, uptr<Hitbox>&& hb) : UICanvas(window, move(hb)) {}

		template<c_ext<VFX> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...> inline T& addVfxNew(Args&&... args) { return addVfx(create<T>(forward<Args>(args)...)); };
		template<c_ext<VFX> T> T& addVfx(uptr<T>&& eff);
		virtual void renderImpl(BatchRenderPass& rp) override;
		virtual void updateImpl() override;
	private:
		vec<uptr<VFX>> vfx;
	};

	template<c_ext<VFX> T> T& UIScreen::addVfx(uptr<T>&& eff)
	{
		T& ref = *eff;
		vfx.push_back(std::move(eff));
		return ref;
	}

	void UIScreen::renderImpl(BatchRenderPass& rp)
	{
		UICanvas::renderImpl(rp);
		for (uptr<VFX>& effect : vfx) {
			effect->render(rp);
		}
	}

	void UIScreen::updateImpl()
	{
		UICanvas::updateImpl();
		std::erase_if(vfx, [](uptr<VFX>& effect) {return effect->tickUpdate();});
	}
}