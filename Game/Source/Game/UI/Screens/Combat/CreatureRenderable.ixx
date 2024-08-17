export module fbc.CreatureRenderable;

import fbc.CombatSquare;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class CreatureRenderable : public UIInteractable {
	public:
		CreatureRenderable(const OccupantObject& creature, Hitbox* hb): UIInteractable(win, hb, creature.getImageField()), creature(creature) {}

		const OccupantObject& creature;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void CreatureRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
	}
}