export module fbc.CardRenderable;

import fbc.Card;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr float CARD_H = 600;
	export constexpr float CARD_W = 300;

	export class CardRenderable : public UIInteractable {
	public:
		CardRenderable(FWindow& window, uptr<Hitbox> hb, const Card& card): UIInteractable(window, move(hb), window.cct.images.uiLightPanel), card(card) {}
		CardRenderable(FWindow& window, Hitbox& source, const Card& card, float offX = 0, float offY = 0): UIInteractable(window, make_unique<RelativeHitbox>(window, source, CARD_W, CARD_H, offX, offY), window.cct.images.uiLightPanel), card(card) {}

		const Card& card;
	};
}