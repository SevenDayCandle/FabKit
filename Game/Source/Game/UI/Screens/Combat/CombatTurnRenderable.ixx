export module fbc.CombatTurnRenderable;

import fbc.CombatTurn;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IDrawable;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class CombatTurnRenderable : public UIInteractable {
	public:
		CombatTurnRenderable(const CombatTurn& turn, Hitbox* hb) : UIInteractable(win, hb, cct.images.uiDarkPanelRound), portrait(turn.source.getImagePortrait()) {}

		IDrawable& portrait;

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;

		// TODO highlight turn owner when hovered
	};

	void CombatTurnRenderable::renderImpl(sdl::SDLBatchRenderPass& rp)
	{
		UIInteractable::renderImpl(rp);
		portrait.draw(rp, hb->x + hb->w / 8, hb->y + hb->h * 0.15f, hb->w / 2, hb->h * 0.7f, win.getW(), win.getH(), rotation, &color);
	}
}