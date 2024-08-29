export module fbc.CombatScreen;

import fbc.Card;
import fbc.CardRenderable;
import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.CombatTurnRenderable;
import fbc.CoreContent;
import fbc.CreatureRenderable;
import fbc.FUtil;
import fbc.FWindow;
import fbc.RelativeHitbox;
import fbc.UICanvas;
import fbc.UIScreen;
import fbc.UITextButton;
import std;

namespace fbc {
	constexpr float CARD_HAND_POS_X = 1000;
	constexpr float CARD_HAND_POS_Y = 1000;
	constexpr float END_TURN_SIZE = 300;
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;
	constexpr float TURN_W = 280;

	export class CombatScreen : public UIScreen, public CombatInstance::IViewSubscriber {
	public:
		CombatScreen(FWindow& window): UIScreen(window),
			cardUI(addNew<UICanvas>(relhb(0, 0, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			fieldUI(addNew<UICanvas>(relhb(TILE_OFFSET, TILE_OFFSET, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			turnUI(addNew<UICanvas>(relhb(0, 0, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			endTurnButton(add(make_unique<UITextButton>(win, relhb(hb->getScaleOffSizeX(0.8), hb->getScaleOffSizeY(0.8), END_TURN_SIZE, END_TURN_SIZE), window.cct.images.uiPanelRound, window.cct.fontRegular(), window.cct.strings.combat_end_turn()))) {
		}

		virtual void onPlayerTurnBegin(const CombatTurn* turn) override;
		virtual void onPlayerTurnEnd(const CombatTurn* turn) override;
		virtual void onTurnAdded(const CombatTurn& turn) override;
		virtual void onTurnChanged(ref_view<const mset<CombatTurn>> turns) override;
		virtual void onTurnRemoved(const CombatTurn* turn) override;
		CardRenderable& createCardRender(const Card& card, float tOffX, float tOffY, float sOffX = 0, float sOffY = 0);
		CombatTurnRenderable& createTurnRender(const CombatTurn& turn);
		CreatureRenderable& createOccupantRender(const OccupantObject& occupant);
		void open() override;
		void removeCardRender(Card* card);
		void removeCardRender(CardRenderable* card);
		void updateImpl() override;
	private:
		CombatInstance* instance;
		UITextButton& endTurnButton;
		UICanvas& cardUI;
		UICanvas& fieldUI;
		UICanvas& turnUI;
		umap<const Card*, CardRenderable*> cardUIMap;
		umap<const CombatTurn*, CombatTurnRenderable*> turnUIMap;
		umap<const OccupantObject*, CreatureRenderable*> occupantUIMap;
	};
}