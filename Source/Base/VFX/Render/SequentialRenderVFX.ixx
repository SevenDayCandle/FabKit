export module fab.SequentialRenderVFX;

import fab.FUtil;
import fab.FWindow;
import fab.SequentialVFX;
import fab.UIImage;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import std;

/* A sequential VFX that takes ownership of an object during its lifetime. Useful for chaining together VFX that relies on a shared UI that should be disposed after they are done */
namespace fab {
	export class SequentialRenderVFX : public SequentialVFX {
	public:
		SequentialRenderVFX(FWindow& window, uptr<UIImage>&& item): SequentialVFX(window), item(move(item)) {}
		SequentialRenderVFX(uptr<UIImage>&& item) : SequentialVFX(item->win), item(move(item)) {}
		template <c_varg<uptr<VFX>>... Args> SequentialRenderVFX(FWindow& window, uptr<UIImage>&& item, Args&&... items) : SequentialVFX(window, move(items)), item(move(item)) {}
		template <c_varg<uptr<VFX>>... Args> SequentialRenderVFX(uptr<UIImage>&& item, Args&&... items) : SequentialVFX(item->win, move(items)), item(move(item)) {}
		virtual ~SequentialRenderVFX() = default;

		uptr<UIImage> item;

		virtual void render(sdl::SDLBatchRenderPass& rp) override;
	};

	void SequentialRenderVFX::render(sdl::SDLBatchRenderPass& rp) {
		SequentialVFX::render(rp);
		item->render(rp);
	}
}