export module fbc.CombatScreen;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatTurn;
import fbc.FUtil;
import fbc.RelativeHitbox;
import fbc.UICanvas;
import fbc.UIScreen;
import std;

namespace fbc {
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;
	constexpr float TURN_W = 280;

	export class CombatScreen : public UIScreen {
	public:
		CombatScreen(): UIScreen(),
			fieldUI(addElement(make_unique<UICanvas>(new RelativeHitbox(*hb, TILE_OFFSET, TILE_OFFSET, hb->getScaleOffsetSizeX(), hb->getScaleOffsetSizeY())))),
			turnUI(addElement(make_unique<UICanvas>(new RelativeHitbox(*hb, 0, 0, hb->getScaleOffsetSizeX(), hb->getScaleOffsetSizeY())))) {
		}

		void createCreatureRender(const OccupantObject* occupant);
		void createTurnRender(const CombatTurn& turn);
		void open() override;
	private:
		CombatInstance* instance;
		UICanvas& fieldUI;
		UICanvas& turnUI;
	};
}