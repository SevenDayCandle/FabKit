export module fbc.CardRenderable;

import fbc.Card;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.UIInteractable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class CardRenderable : public UIInteractable {
	public:
		CardRenderable(FWindow& window, uptr<Hitbox> hb, const Card& card): UIInteractable(window, move(hb), window.cct.images.uiDarkPanelRound), card(card) {}

		const Card& card;
	};
}