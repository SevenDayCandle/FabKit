export module fbc.StatusTurnMode;

import fbc.FUtil;

namespace fbc {
	export enum StatusTurnMode {
		NONE,
		ROUND_BEGIN,
		ROUND_END,
		TURN_BEGIN,
		TURN_END,
	};

	export ilist<StatusTurnMode> WINDOWMODE_ALL = { NONE, ROUND_BEGIN, ROUND_END, TURN_BEGIN, TURN_END };
}