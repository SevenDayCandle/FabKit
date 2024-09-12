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
import fbc.UICanvas;
import fbc.UIScreen;
import fbc.UITextButton;
import sdl.SDLBase;
import std;

namespace fbc {
	constexpr float CARD_HAND_POS_X_PCT = 0.25f;
	constexpr float CARD_HAND_POS_Y_DIFF = 100;
	constexpr float END_TURN_SIZE = 300;
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;
	constexpr float TURN_W = 280;

	export class CombatScreen : public UIScreen, public CombatInstance::IViewSubscriber {
	public:
		CombatScreen(FWindow& window): UIScreen(window),
			cardUI(addNew<UICanvas<CardRenderable>>(relhb(hb->getScaleOffSizeX() * CARD_HAND_POS_X_PCT, hb->getScaleOffSizeY() - CARD_HAND_POS_Y_DIFF - CARD_H, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			fieldUI(addNew<UICanvas<CombatSquareRenderable>>(relhb(TILE_OFFSET, TILE_OFFSET, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			turnUI(addNew<UICanvas<CombatTurnRenderable>>(relhb(0, 0, TILE_SIZE, hb->getScaleOffSizeY()))),
			creatureUI(addNew<UICanvas<CreatureRenderable>>(fieldUI.relhb(0, 0, hb->getScaleOffSizeX(), hb->getScaleOffSizeY()))),
			endTurnButton(add(make_unique<UITextButton>(win, relhb(hb->getScaleOffSizeX(0.8), hb->getScaleOffSizeY(0.8), END_TURN_SIZE, END_TURN_SIZE), window.cct.images.uiPanelRound, window.cct.fontRegular(), window.cct.strings.combat_end_turn()))) {
		}

		inline void resetHighlightDistance() { highlightDistance(instance->getDistanceSource(), &sdl::COLOR_STANDARD, &sdl::COLOR_STANDARD, 0, 0, 0, 0, 0); }

		virtual void onPlayerTurnBegin(const CombatTurn* turn) override;
		virtual void onPlayerTurnEnd(const CombatTurn* turn) override;
		virtual void onTurnAdded(const CombatTurn& turn) override;
		virtual void onTurnChanged(ref_view<const mset<CombatTurn>> turns) override;
		virtual void onTurnRemoved(const CombatTurn* turn) override;
		CardRenderable& createCardRender(const Card& card, float tOffX, float sOffX = 0, float sOffY = CARD_H * 2);
		CombatTurnRenderable& createTurnRender(const CombatTurn& turn);
		CreatureRenderable& createOccupantRender(const OccupantObject& occupant);
		void highlightDistance(CombatSquare* object, const sdl::Color* color, const sdl::Color* moveColor, int highlightRangeBegin, int highlightRangeEnd, int movementRange, int targetSizeX, int targetSizeY);
		void open() override;
		void recolorSquare(CombatSquareRenderable& square);
		void removeCardRender(Card* card);
		void removeCardRender(CardRenderable* card);
		void selectCardRender(CardRenderable* card);
		void updateImpl() override;
	private:
		CardRenderable* selectedCard;
		CombatInstance* instance;
		CombatSquare* distanceSource;
		CombatSquare* targetingSource;
		const sdl::Color* halfColor = &sdl::COLOR_STANDARD;
		const sdl::Color* targetingColor = &sdl::COLOR_STANDARD;
		int highlightRangeBegin;
		int highlightRangeEnd;
		int movementRange;
		int targetSizeX;
		int targetSizeY;
		UITextButton& endTurnButton;
		UICanvas<CardRenderable>& cardUI;
		UICanvas<CombatSquareRenderable>& fieldUI;
		UICanvas<CombatTurnRenderable>& turnUI;
		UICanvas<CreatureRenderable>& creatureUI;
		umap<const Card*, CardRenderable*> cardUIMap;
		umap<const CombatTurn*, CombatTurnRenderable*> turnUIMap;
		umap<const OccupantObject*, CreatureRenderable*> occupantUIMap;
	};
}