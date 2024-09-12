export module fbc.CombatSquare;

import fbc.AttributeObject;
import fbc.FieldObject;
import fbc.FUtil;
import fbc.IDrawable;
import fbc.TurnObject;
import std;

namespace fbc {
	export class CombatSquare : FieldObject {
	public:
		class OccupantObject : public FieldObject, public TurnObject {
		public:
			OccupantObject() {}
			OccupantObject(OccupantObject&& other) = default;
			virtual ~OccupantObject() override = default;

			CombatSquare* currentSquare;

			virtual inline int getMovement() { return 0; }
			virtual inline void postInitialize() {}
			virtual inline void queueTurn() {}

			virtual IDrawable& getImageField() const = 0;
		};

		CombatSquare(int col, int row): col(col), row(row) {}

		int col;
		int row;
		int sDist;

		inline int getLineDistance(const CombatSquare& other) const { return getLineDistance(other.col, other.row); }
		inline int getLineDistance(int tCol, int tRow) const { return std::max(std::abs(tCol - col), std::abs(tRow - row)); }
		inline OccupantObject* getOccupant() const { return occupant; }

		bool passable();
		CombatSquare& setOccupant(OccupantObject* occupant);
	private:
		OccupantObject* occupant = nullptr;
	};

	export using OccupantObject = CombatSquare::OccupantObject;
}