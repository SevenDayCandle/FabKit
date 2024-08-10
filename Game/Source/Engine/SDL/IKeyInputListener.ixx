export module sdl.IKeyInputListener;

import std;

export namespace sdl {
	export struct IKeyInputListener {
	public:
		IKeyInputListener() {}
		virtual ~IKeyInputListener() = default;

		virtual void onKeyPress(std::int32_t c) = 0;
		virtual void onTextInput(const char* text) = 0;
	};
}