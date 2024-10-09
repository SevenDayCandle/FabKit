export module fbc.CombatSquareRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.UICallbackInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class CombatSquareRenderable : public UICallbackInteractable<CombatSquareRenderable> {
	public:
		CombatSquareRenderable(FWindow& window, uptr<Hitbox>&& hb, const CombatSquare& square): UICallbackInteractable<CombatSquareRenderable>(window, move(hb), window.props.defaultPanel()), square(square) {}

		bool valid;
		const CombatSquare& square;
		const sdl::Color* originalColor = &sdl::COLOR_STANDARD;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void CombatSquareRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIImage::renderImpl(rp);
	}
}