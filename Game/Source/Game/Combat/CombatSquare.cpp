module;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.UIBase;
import std;

module fbc.CombatSquare;

namespace fbc {

	// Whether the square can be moved through or not
	// TODO implement
	bool CombatSquare::passable()
	{
		return true;
	}

	// Assign the given occupant to this square
	CombatSquare& CombatSquare::setOccupant(OccupantObject* occupant)
	{
		this->occupant = occupant;
		if (occupant) {
			occupant->currentSquare = this;
			occupant->onMoved();
		}
		// TODO hooks
		// TODO power triggers

		return *this;
	}
}