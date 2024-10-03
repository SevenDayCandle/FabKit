export module fbc.CreatureMoveAction;

import fbc.CallbackAction;
import fbc.CallbackVFX;
import fbc.CombatSquare;
import fbc.FUtil;
import fbc.VFXAction;
import std;

namespace fbc {
	export class CreatureMoveAction : public VFXAction<CreatureMoveAction> {
	public:
		CreatureMoveAction(OccupantObject* occupant, CombatSquare* target, const func<uptr<CallbackVFX>()>& vfxFunc): VFXAction(vfxFunc), target(target), occupant(occupant) {}
		virtual ~CreatureMoveAction() = default;

		CombatSquare* target;
		OccupantObject* occupant;

		virtual void start() override;
	};

	void CreatureMoveAction::start() {
		if (target) {
			target->setOccupant(occupant);
		}
		else if (occupant) {
			occupant->currentSquare = nullptr;
			occupant->onMoved();
		}
	}
}