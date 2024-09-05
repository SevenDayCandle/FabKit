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
	export constexpr float CARD_W = 400;

	export class CardRenderable : public UIInteractable {
	public:
		CardRenderable(FWindow& window, uptr<Hitbox> hb, const Card& card): UIInteractable(window, move(hb), window.cct.images.uiPanel), card(card) {}
		CardRenderable(FWindow& window, Hitbox& source, const Card& card, float offX = 0, float offY = 0): UIInteractable(window, make_unique<RelativeHitbox>(window, source, offX, offY, CARD_W, CARD_H), window.cct.images.uiPanel), card(card) {}

		inline CardRenderable& setOnClick(const func<void(CardRenderable&)>& onClick) { return this->onLeftClick = onClick, *this; }
		inline CardRenderable& setOnHover(const func<void(CardRenderable&)>& onHover) { return this->onHover = onHover, *this; }
		inline CardRenderable& setOnRightClick(const func<void(CardRenderable&)>& onRightClick) { return this->onRightClick = onRightClick, *this; }
		inline CardRenderable& setOnUnhover(const func<void(CardRenderable&)>& onUnhover) { return this->onHover = onUnhover, *this; }

		const Card& card;
	private:
		func<void(CardRenderable&)> onHover;
		func<void(CardRenderable&)> onLeftClick;
		func<void(CardRenderable&)> onRightClick;
		func<void(CardRenderable&)> onUnhover;

		virtual void clickLeftEvent() override;
		virtual void clickRightEvent() override;
	};

	void CardRenderable::clickLeftEvent() {
		if (this->onLeftClick) {
			this->onLeftClick(*this);
		}
	}

	void CardRenderable::clickRightEvent() {
		if (this->onRightClick) {
			this->onRightClick(*this);
		}
	}
}