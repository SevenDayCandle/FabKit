module;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.CreatureRenderable;
import fbc.GameRun;
import fbc.RelativeHitbox;

module fbc.CombatScreen;

namespace fbc {
	void CombatScreen::createCreatureRender(const OccupantObject* occupant)
	{
		CombatSquare* square = occupant->currentSquare;
		float offX = TILE_OFFSET;
		float offY = TILE_OFFSET;
		if (square) {
			offX = TILE_OFFSET + square->col * TILE_SIZE;
			offY = TILE_OFFSET + square->row * TILE_SIZE;
		}
		addElement(make_unique<CreatureRenderable>(*occupant, new RelativeHitbox(*hb, offX, offY, TILE_SIZE, TILE_SIZE)));
	}

	void CombatScreen::open()
	{
		GameRun* run = GameRun::current.get();
		CombatInstance* instance = run->getCombatInstance();
		// Add buttons for each square
		for (const CombatSquare& square : instance->getSquares()) {
			addElement(make_unique<CombatSquareRenderable>(square, new RelativeHitbox(*hb, TILE_OFFSET + square.col * TILE_SIZE, TILE_OFFSET + square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE)));
		}
		// Add images for each creature
		for (const OccupantObject* occupant : instance->getOccupants()) {
			createCreatureRender(occupant);
		}
	}
}