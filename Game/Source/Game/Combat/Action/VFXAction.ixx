export module fbc.VFXAction;

import fbc.Action;
import fbc.CallbackAction;
import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.UIScreen;
import std;

namespace fbc {
	export template <typename T = Action> class VFXAction : public CallbackAction<T> {
	public:
		VFXAction(const func<uptr<CallbackVFX>()>& vfxFunc) : CallbackAction<T>(), vfxFunc(vfxFunc) {}
		VFXAction(func<uptr<CallbackVFX>()>&& vfxFunc) : CallbackAction<T>(), vfxFunc(move(vfxFunc)) {}
		VFXAction(uptr<CallbackVFX>&& vfx) : CallbackAction<T>(), vfxFunc([v = move(vfx)]() mutable {
			return move(v);
		}) {}

		bool isDone = false;

		inline virtual bool run() override { return isDone; }

		virtual void start() override;
	protected:
		func<uptr<CallbackVFX>()> vfxFunc;
	};

	template <typename T> void VFXAction<T>::start()
	{
		uptr<CallbackVFX> vfx = vfxFunc();
		if (vfx) {
			UIScreen* screen = dynamic_cast<UIScreen*>(vfx->win.currentScreen());
			if (screen) {
				vfx->setOnComplete([this](CallbackVFX& v) {isDone = true; });
				screen->addVfx(move(vfx));
			}
			else {
				isDone = true;
			}
		}
		else {
			isDone = true;
		}
	}
}