export module sdl.iKeyInputListener;

import std;

export namespace sdl {
	export class IKeyInputListener {
	public:
		IKeyInputListener() {}
		virtual ~IKeyInputListener() {}

		virtual void onKeyPress(std::int32_t c) = 0;
		virtual void onTextInput(char* text) = 0;
	};
}