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

		template <c_ext<VFX> T> inline T& addEffect(uptr<T>&& act) {
			T& ref = *act;
			effects.push_back(move(act));
			return ref;
		}
		template <c_ext<VFX> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...> inline T& addNew(Args&&... args) { return addEffect(create<T>(forward<Args>(args)...)); }
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
		if (executeIndex < effects.size()) {
			effects[executeIndex]->render(rp);
		}
	}

	void SequentialVFX::update() {
		if (executeIndex < effects.size()) {
			effects[executeIndex]->update();
		}
	}
}