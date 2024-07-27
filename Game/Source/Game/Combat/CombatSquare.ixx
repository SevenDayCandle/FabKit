export module fbc.CombatSquare;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IDrawable;
import std;

namespace fbc {
	export class CombatSquare : FieldObject {
	public:
		class OccupantObject : public FieldObject {
		public:
			OccupantObject() {}
			OccupantObject(OccupantObject&& other) = default;
			virtual ~OccupantObject() override = default;

			CombatSquare* currentSquare;

			virtual IDrawable& getImageField() = 0;
			virtual IDrawable& getImagePortrait() = 0;
		};

		CombatSquare(int col, int row): col(col), row(row) {}

		int col;
		int row;

		inline bool onTurnBegin() override { return true; }
		inline OccupantObject* getOccupant() const { return occupant; }

		CombatSquare& setOccupant(OccupantObject* occupant);
	private:
		OccupantObject* occupant = nullptr;
	};

	export using OccupantObject = CombatSquare::OccupantObject;
}