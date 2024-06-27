export module fbc.CombatSquare;

import fbc.FieldObject;
import fbc.FUtil;
import fbc.Status;
import std;

export namespace fbc {
	export class CombatSquare {
	public:
		CombatSquare() {}

		FieldObject* occuptant;
		vec<uptr<Status>> statuses;
	};
}