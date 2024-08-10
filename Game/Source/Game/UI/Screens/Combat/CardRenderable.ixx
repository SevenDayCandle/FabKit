export module fbc.CardRenderable;

import fbc.Card;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl;
import std;

namespace fbc {
	export class CardRenderable : public UIInteractable {
	public:
		CardRenderable(const Card& card, Hitbox* hb): UIInteractable(hb, cct.images.uiDarkPanelRound), card(card) {}

		const Card& card;
	};
}