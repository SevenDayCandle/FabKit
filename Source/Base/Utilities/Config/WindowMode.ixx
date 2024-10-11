export module fab.WindowMode;

import fab.FUtil;

namespace fab {
	export enum WindowMode {
		WINDOWED,
		FULLSCREEN,
		BORDERLESS_FULLSCREEN
	};

	export ilist<WindowMode> WINDOWMODE_ALL = { WINDOWED, FULLSCREEN, BORDERLESS_FULLSCREEN };
}