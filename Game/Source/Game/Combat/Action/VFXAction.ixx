export module fbc.VFXAction;

import fbc.Action;
import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.FWindow;
import fbc.UIScreen;
import std;

namespace fbc {
	export class VFXAction : public Action {
	public:
		VFXAction(FWindow& window, uptr<CallbackVFX>&& vfx): Action(), vfx(move(vfx)), win(window) {}

		bool isDone;
		FWindow& win;
		uptr<CallbackVFX> vfx;

		inline virtual bool run() override { return isDone; }

		virtual void start() override;
	};

	void VFXAction::start()
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