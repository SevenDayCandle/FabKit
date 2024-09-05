export module fbc.CombatScreen;

import fbc.Card;
import fbc.CardRenderable;
import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.CombatTurn;
import fbc.CombatTurnRenderable;
import fbc.CoreContent;
import fbc.CreatureRenderable;
import fbc.FUtil;
import fbc.FWindow;
import fbc.RelativeHitbox;
import fbc.UIGrid;
import fbc.UIScreen;
import fbc.UITextButton;
import std;

namespace fbc {
	constexpr float CARD_HAND_POS_X = 0.25f;
	constexpr float CARD_HAND_POS_Y = 0.75f;
	constexpr float END_TURN_SIZE = 300;
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;
	constexpr float TURN_W = 280;

	export class CombatScreen : public UIScreen, public CombatInstance::IViewSubscriber {
	public:
		CombatScreen(FWindow& window): UIScreen(window),
			cardUI(addNew<UIGrid<CardRenderable>>(relhb(hb->getScaleOffSizeX()* CARD_HAND_POS_X, hb->getScaleOffSizeY()* CARD_HAND_POS_Y, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()), CARD_W, CARD_H)),
			fieldUI(addNew<UIGrid<CombatSquareRenderable>>(relhb(TILE_OFFSET, TILE_OFFSET, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()), TILE_SIZE, TILE_SIZE)),
			turnUI(addNew<UIGrid<CombatTurnRenderable>>(relhb(0, 0, TILE_SIZE, hb->getScaleOffSizeY()), TURN_W, TILE_SIZE)),
			creatureUI(addNew<UIGrid<CreatureRenderable>>(fieldUI.relhb(0, 0, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()), TILE_SIZE, TILE_SIZE)),
			endTurnButton(add(make_unique<UITextButton>(win, relhb(hb->getScaleOffSizeX(0.8), hb->getScaleOffSizeY(0.8), END_TURN_SIZE, END_TURN_SIZE), window.cct.images.uiPanelRound, window.cct.fontRegular(), window.cct.strings.combat_end_turn()))) {
		}

		inline float cardHandStartX() const { return hb->getScaleOffSizeX() * CARD_HAND_POS_X; }
		inline float cardHandStartY() const { return hb->getScaleOffSizeY() * CARD_HAND_POS_Y; }

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
		void selectCardRender(CardRenderable* card);
		void updateImpl() override;
	private:
		CardRenderable* selectedCard;
		CombatInstance* instance;
		CombatSquare* distanceSource;
		CombatSquare* targetingSource;
		UITextButton& endTurnButton;
		UIGrid<CardRenderable>& cardUI;
		UIGrid<CombatSquareRenderable>& fieldUI;
		UIGrid<CombatTurnRenderable>& turnUI;
		UIGrid<CreatureRenderable>& creatureUI;
		umap<const Card*, CardRenderable*> cardUIMap;
		umap<const CombatTurn*, CombatTurnRenderable*> turnUIMap;
		umap<const OccupantObject*, CreatureRenderable*> occupantUIMap;
	};
}