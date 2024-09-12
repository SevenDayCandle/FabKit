export module fbc.VFXAction;

import fbc.Action;
import fbc.CallbackAction;
import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.UIScreen;
import std;

namespace fbc {
	export template <c_ext<Action> T = Action> class VFXAction : public CallbackAction<T> {
	public:
		VFXAction(FWindow& window, uptr<CallbackVFX>&& vfx): CallbackAction<T>(), vfx(move(vfx)), win(window) {}

		bool isDone;
		FWindow& win;

		inline virtual bool run() override { return isDone; }

		virtual void start() override;
	protected:
		uptr<CallbackVFX> vfx;
	};

	template <c_ext<Action> T> void VFXAction<T>::start()
	{
		UIScreen* screen = dynamic_cast<UIScreen*>(win.currentScreen());
		if (screen) {
			vfx->setOnComplete([this](CallbackVFX& v) {isDone = true; });
			screen->addVfx(move(vfx));
		}
		else {
			isDone = true;
		}
	}
}