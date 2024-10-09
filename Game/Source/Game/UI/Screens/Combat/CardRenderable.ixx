export module fbc.CardRenderable;

import fbc.Card;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.UICallbackInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr float CARD_H = 600;
	export constexpr float CARD_W = 400;

	export class CardRenderable : public UICallbackInteractable<CardRenderable> {
	public:
		CardRenderable(FWindow& window, uptr<Hitbox> hb, const Card& card) : UICallbackInteractable<CardRenderable>(window, move(hb), window.props.defaultPanel()), card(card) {}
		CardRenderable(FWindow& window, Hitbox& source, const Card& card, float offX = 0, float offY = 0) : UICallbackInteractable<CardRenderable>(window, make_unique<RelativeHitbox>(window, source, offX, offY, CARD_W, CARD_H), window.props.defaultPanel()), card(card) {}

		const Card& card;
	};
}