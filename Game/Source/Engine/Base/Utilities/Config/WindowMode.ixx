export module fbc.WindowMode;

import fbc.FUtil;

export namespace fbc {
	export enum WindowMode {
		WINDOWED,
		FULLSCREEN,
		BORDERLESS_FULLSCREEN
	};

	export ilist<WindowMode> WINDOWMODE_ALL = { WINDOWED, FULLSCREEN, BORDERLESS_FULLSCREEN };
}