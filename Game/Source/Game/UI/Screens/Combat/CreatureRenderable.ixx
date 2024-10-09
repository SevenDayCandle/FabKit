export module fbc.CreatureRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class CreatureRenderable : public UIInteractable {
	public:
		CreatureRenderable(FWindow& window, uptr<Hitbox> hb, const OccupantObject& creature): UIInteractable(window, move(hb), creature.getImageField()), creature(creature) {}

		const OccupantObject& creature;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void CreatureRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
	}
}