export module fbc.CombatRoom;

import fbc.FUtil;
import fbc.GameRun;
import fbc.RunRoom;
import fbc.RunZone;
import std;

namespace fbc {
	export class CombatRoom : public RunRoom::RoomType {
	public:
		CombatRoom(): RunRoom::RoomType(ID, 45) {}

		static constexpr strv ID = "CombatRoom";
		static const CombatRoom instance;

		void onEnter() override;
	};

	const CombatRoom CombatRoom::instance = CombatRoom();

	// Start combat upon entering
	void CombatRoom::onEnter()
	{
		GameRun::current->startCombat();
	}
}