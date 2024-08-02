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
		CombatTurnRenderable(const CombatTurn& turn, Hitbox* hb) : UIInteractable(hb, cct.images.darkPanelRound), turn(turn), portrait(turn.source.getImagePortrait()) {}

		const CombatTurn& turn;
		IDrawable& portrait;

		virtual void renderImpl() override;

		// TODO highlight turn owner when hovered
	};

	void CombatTurnRenderable::renderImpl()
	{
		UIInteractable::renderImpl();
		portrait.draw(hb.get());
	}
}