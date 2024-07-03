module;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.UIBase;
import std;

module fbc.CombatSquare;

namespace fbc {

	// Assign the given occupant to this square
	CombatSquare& CombatSquare::setOccupant(FieldObject* occupant)
	{
		this->occupant = occupant;
		if (occupant) {
			occupant->currentSquare = this;
		}
		// TODO hooks
		// TODO power triggers

		return *this;
	}
}