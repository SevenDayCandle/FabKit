export module fbc.CardRenderable;

import fbc.Card;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIBase;
import sdl;
import std;

namespace fbc {
	export class CardRenderable : public UIBase {
	public:
		CardRenderable(Card& card, Hitbox* hb): UIBase(hb), card(card) {}
		virtual ~CardRenderable() {}

		Card& card;
	};
}