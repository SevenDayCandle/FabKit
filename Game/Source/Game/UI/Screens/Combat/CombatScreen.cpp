module;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.GameRun;
import fbc.RelativeHitbox;

module fbc.CombatScreen;

namespace fbc {
	void CombatScreen::open()
	{
		GameRun* run = GameRun::current.get();
		CombatInstance* instance = run->getCombatInstance();
		// Add buttons for each square
		for (const CombatSquare& square : instance->getSquares()) {
			addElement(make_unique<CombatSquareRenderable>(square, new RelativeHitbox(*hb, TILE_OFFSET + square.col * TILE_SIZE, TILE_OFFSET + square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE)));
		}
		// Add images for each creature

	}
}