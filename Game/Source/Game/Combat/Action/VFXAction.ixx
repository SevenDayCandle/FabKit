export module fbc.VFXAction;

import fbc.Action;
import fbc.CallbackVFX;
import fbc.FUtil;
import fbc.ScreenManager;
import fbc.UIBase;
import std;

namespace fbc {
	export class VFXAction : public Action {
	public:
		VFXAction(uptr<CallbackVFX>&& vfx): Action(), vfx(move(vfx)) {}

		bool isDone;
		uptr<CallbackVFX> vfx;

		inline virtual bool run() override { return isDone; }

		virtual void start() override;
	};

	void VFXAction::start()
	{
		UIBase* screen = screenManager::currentScreen();
		if (screen) {
			vfx->setOnComplete([this](CallbackVFX& v) {isDone = true; });
			screen->addVFX(move(vfx));
		}
		else {
			isDone = true;
		}
	}
}