export module fbc.CombatRoom;

import fbc.CombatScreen;
import fbc.FUtil;
import fbc.GameRun;
import fbc.RunRoom;
import fbc.RunZone;
import fbc.ScreenManager;
import std;

namespace fbc {
	export class CombatRoom : public RunRoom::RoomType {
	public:
		CombatRoom(): RunRoom::RoomType(ID, 45) {}

		static constexpr strv ID = "COMBAT";
		static const CombatRoom instance;

		void onAfterClick() override;
		void onEnter() override;
	};

	const CombatRoom CombatRoom::instance = CombatRoom();

	void CombatRoom::onAfterClick()
	{
		if (GameRun::current->getCombatInstance() != nullptr) {
			screenManager::openScreen(make_unique<CombatScreen>());
		}
	}

	// Start combat upon entering
	void CombatRoom::onEnter()
	{
		GameRun::current->startCombat();
	}
}