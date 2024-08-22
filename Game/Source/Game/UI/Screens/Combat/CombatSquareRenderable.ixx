export module fbc.CombatSquareRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class CombatSquareRenderable : public UIInteractable {
	public:
		CombatSquareRenderable(FWindow& window, uptr<Hitbox>&& hb, const CombatSquare& square): UIInteractable(window, move(hb), cct.images.uiLightPanel), square(square) {}

		const CombatSquare& square;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void CombatSquareRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
	}
}