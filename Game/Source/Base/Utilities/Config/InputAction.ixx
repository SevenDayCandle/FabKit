export module fbc.inputAction;

import fbc.futil;
import raylib;

export namespace fbc {
	export class InputAction {
	public:
		str ID;
		raylib::KeyboardKey key;
		raylib::GamepadButton button;
	};
}