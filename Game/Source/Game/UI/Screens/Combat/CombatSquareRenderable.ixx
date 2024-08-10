export module fbc.CombatSquareRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class CombatSquareRenderable : public UIInteractable {
	public:
		CombatSquareRenderable(const CombatSquare& square, Hitbox* hb): UIInteractable(hb, cct.images.uiLightPanel), square(square) {}

		const CombatSquare& square;

		virtual void renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) override;
	};

	void CombatSquareRenderable::renderImpl(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp)
	{
		UIInteractable::renderImpl(cd, rp);
	}
}