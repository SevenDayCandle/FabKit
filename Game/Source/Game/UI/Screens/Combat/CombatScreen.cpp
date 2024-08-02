module;

import fbc.CombatInstance;
import fbc.CombatSquare;
import fbc.CombatSquareRenderable;
import fbc.CombatTurnRenderable;
import fbc.CreatureRenderable;
import fbc.GameRun;
import fbc.RelativeHitbox;

module fbc.CombatScreen;

namespace fbc {
	void CombatScreen::createCreatureRender(const OccupantObject* occupant)
	{
		CombatSquare* square = occupant->currentSquare;
		float offX = 0;
		float offY = 0;
		if (square) {
			offX = square->col * TILE_SIZE;
			offY = square->row * TILE_SIZE;
		}
		fieldUI.addElement(make_unique<CreatureRenderable>(*occupant, new RelativeHitbox(*fieldUI.hb, offX, offY, TILE_SIZE, TILE_SIZE)));
	}

	void CombatScreen::createTurnRender(const CombatTurn& turn)
	{
		CombatTurnRenderable* render = &turnUI.addElement(make_unique<CombatTurnRenderable>(turn, new RelativeHitbox(*turnUI.hb, 0, turnUI.size() * TILE_SIZE, TURN_W, TILE_SIZE)));
	}

	void CombatScreen::open()
	{
		GameRun* run = GameRun::current.get();
		instance = run->getCombatInstance();
		// Add buttons for each square
		for (const CombatSquare& square : instance->getSquares()) {
			fieldUI.addElement(make_unique<CombatSquareRenderable>(square, new RelativeHitbox(*fieldUI.hb, square.col * TILE_SIZE, square.row * TILE_SIZE, TILE_SIZE, TILE_SIZE)));
		}
		// Add images for each creature
		for (const OccupantObject* occupant : instance->getOccupants()) {
			createCreatureRender(occupant);
		}
		// Add images for each turn
		for (const CombatTurn& turn : instance->getTurns()) {
			createTurnRender(turn);
		}
	}
}