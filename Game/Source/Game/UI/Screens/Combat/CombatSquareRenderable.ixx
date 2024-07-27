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
		CombatSquareRenderable(const CombatSquare& square, Hitbox* hb): UIInteractable(hb, cct.images.lightPanel), square(square) {}

		const CombatSquare& square;

		virtual void renderImpl() override;
	};

	void CombatSquareRenderable::renderImpl()
	{
		UIInteractable::renderImpl();
	}
}