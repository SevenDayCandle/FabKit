module;

import fbc.CombatSquare;
import fbc.GameRun;

module fbc.Card;

namespace fbc {

	// Get the pile that the card should be moved to once used
	const PileType& Card::getPileAfterUse()
	{
		// TODO expend check
		// TODO card modifier checks
		return piletype::DISCARD;
	}

	// Activate the card's effects on all allowed targets in the card's radius, centered on square
	void Card::use(GameObject* source, CombatSquare& square)
	{
		// TODO
		// TODO hooks
	}
}