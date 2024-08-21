export module fbc.CombatSquareRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
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
		CombatSquareRenderable(const CombatSquare& square, Hitbox* hb): UIInteractable(win, hb, cct.images.uiLightPanel), square(square) {}

		const CombatSquare& square;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void CombatSquareRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
	}
}