export module fab.MultiVFX;

import fab.CallbackVFX; 
import fab.FUtil;
import fab.FWindow;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;
namespace fab {
	export class MultiVFX : public CallbackVFX {
	public:
		MultiVFX(FWindow& window) : CallbackVFX(window) {}
		template <c_varg<uptr<VFX>>... Args> MultiVFX(FWindow& window, Args&&... items) : CallbackVFX(window, std::max({ items->duration... })) {
			effects.reserve(sizeof...(items));
			(effects.push_back(move(items)), ...);
		}
		virtual ~MultiVFX() = default;

		inline MultiVFX& addEffect(uptr<VFX>&& act) { return effects.push_back(move(act)), * this; }
		template <c_varg<uptr<VFX>&&>... Args> inline MultiVFX& addEffects(Args&&... items) { return (effects.push_back(move(items)), ...), * this; }

		virtual bool tickUpdate() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
		virtual void update() override;
	protected:
		vec<uptr<VFX>> effects;
		vec<uptr<VFX>> oldEffects;
	};

	bool MultiVFX::tickUpdate() {
		if (effects.empty()) {
			return true;
		}
		for (auto it = effects.begin(); it != effects.end();) {
			if (it->get()->tickUpdate()) {
				oldEffects.push_back(move(*it));
				it = effects.erase(it);
			}
			else {
				++it;
			}
		}
		return false;
	}

	void MultiVFX::render(sdl::SDLBatchRenderPass& rp) {
		for (uptr<VFX>& effect : effects) {
			effect->render(rp);
		}
	}

	void MultiVFX::update() {
		for (uptr<VFX>& effect : effects) {
			effect->update();
		}
	}
}