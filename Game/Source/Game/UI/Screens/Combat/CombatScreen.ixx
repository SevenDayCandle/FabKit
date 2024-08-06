export module fbc.CombatScreen;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.CombatTurnRenderable;
import fbc.CoreContent;
import fbc.CreatureRenderable;
import fbc.FUtil;
import fbc.RelativeHitbox;
import fbc.UICanvas;
import fbc.UIScreen;
import fbc.UITextButton;
import std;

namespace fbc {
	constexpr float END_TURN_SIZE = 300;
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;
	constexpr float TURN_W = 280;

	export class CombatScreen : public UIScreen, public CombatInstance::IViewSubscriber {
	public:
		CombatScreen(): UIScreen(),
			fieldUI(add(make_unique<UICanvas>(new RelativeHitbox(*hb, TILE_OFFSET, TILE_OFFSET, hb->getScaleOffSizeX(), hb->getScaleOffSizeY())))),
			turnUI(add(make_unique<UICanvas>(new RelativeHitbox(*hb, 0, 0, hb->getScaleOffSizeX(), hb->getScaleOffSizeY())))),
			endTurnButton(add(make_unique<UITextButton>(new RelativeHitbox(*hb, hb->getScaleOffSizeX(0.8), hb->getScaleOffSizeY(0.8), END_TURN_SIZE, END_TURN_SIZE),
				cct.images.panelRound, cct.fontRegular(), cct.strings.combat_end_turn()))) {
		}

		virtual void onPlayerTurnBegin(const CombatTurn* turn) override;
		virtual void onPlayerTurnEnd(const CombatTurn* turn) override;
		virtual void onTurnAdded(const CombatTurn& turn) override;
		virtual void onTurnChanged(ref_view<const mset<CombatTurn>> turns) override;
		virtual void onTurnRemoved(const CombatTurn* turn) override;
		void createOccupantRender(const OccupantObject* occupant);
		void createTurnRender(const CombatTurn& turn);
		void open() override;
		void updateImpl() override;
	private:
		CombatInstance* instance;
		UITextButton& endTurnButton;
		UICanvas& fieldUI;
		UICanvas& turnUI;
		umap<const CombatTurn*, CombatTurnRenderable*> turnUIMap;
		umap<const OccupantObject*, CreatureRenderable*> occupantUIMap;
	};
}