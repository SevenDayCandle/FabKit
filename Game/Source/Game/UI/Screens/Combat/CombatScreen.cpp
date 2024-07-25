module;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.GameRun;

module fbc.CombatScreen;

namespace fbc {
	void CombatScreen::open()
	{
		CombatInstance* instance = GameRun::current->getCombatInstance();
		// Add buttons for each square
	}
}