export module fbc.CombatScreen;

import fbc.FUtil;
import fbc.UIButton;
import fbc.UIScreen;
import fbc.UITextButton;
import std;

namespace fbc {
	constexpr float TILE_OFFSET = 300;
	constexpr float TILE_SIZE = 128;

	export class CombatScreen : public UIScreen {
	public:
		CombatScreen(): UIScreen() {}
		virtual ~CombatScreen() = default;

		void open() override;
	};
}