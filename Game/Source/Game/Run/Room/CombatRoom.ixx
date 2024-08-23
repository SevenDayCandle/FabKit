export module fbc.CombatRoom;

import fbc.CombatScreen;
import fbc.FUtil;
import fbc.FWindow;
import fbc.GameRun;
import fbc.RunRoom;
import fbc.RunZone;
import std;

namespace fbc {
	export class CombatRoom : public RunRoom::RoomType {
	public:
		CombatRoom(): RunRoom::RoomType(ID, 45) {}

		static constexpr strv ID = "COMBAT";
		static const CombatRoom instance;

		void onAfterClick(FWindow& win) override;
		void onEnter() override;
	};

	const CombatRoom CombatRoom::instance = CombatRoom();

	void CombatRoom::onAfterClick(FWindow& window)
	{
		if (GameRun::current->getCombatInstance() != nullptr) {
			window.openScreen(make_unique<CombatScreen>(window));
		}
	}

	// Start combat upon entering
	void CombatRoom::onEnter()
	{
		GameRun::current->startCombat();
	}
}