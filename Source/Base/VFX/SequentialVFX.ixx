export module fab.SequentialVFX;

import fab.CallbackVFX;
import fab.FUtil;
import fab.FWindow;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class SequentialVFX : public CallbackVFX {
	public:
		SequentialVFX(FWindow& window): CallbackVFX(window) {}
		template <c_varg<uptr<VFX>>... Args> SequentialVFX(FWindow& window, Args&&... items) : CallbackVFX(window) {
			effects.reserve(sizeof...(items));
			(effects.push_back(move(items)), ...);
		}
		virtual ~SequentialVFX() = default;

		inline SequentialVFX& addEffect(uptr<VFX>&& act) { return effects.push_back(move(act)), * this; }
		template <c_varg<uptr<VFX>&&>... Args> inline SequentialVFX& addEffects(Args&&... items) { return (effects.push_back(move(items)), ...), * this; }

		virtual bool tickUpdate() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void update() override;
	protected:
		vec<uptr<VFX>> effects;
	private:
		int executeIndex = 0;
	};

	bool SequentialVFX::tickUpdate() {
		if (executeIndex < effects.size()) {
			if (effects[executeIndex]->tickUpdate()) {
				effects[executeIndex]->dispose();
				++executeIndex;
			}
			return false;
		}
		dispose();
		return true;
	}

	void SequentialVFX::render(sdl::SDLBatchRenderPass& rp) {
		effects[executeIndex]->render(rp);
	}

	void SequentialVFX::update() {
		if (executeIndex < effects.size()) {
			effects[executeIndex]->update();
		}
	}
}