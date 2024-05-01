export module sdl.iKeyboardListener;


export namespace sdl {
	export class IKeyboardListener {
	public:
		IKeyboardListener() {}
		virtual ~IKeyboardListener() {}

		virtual void onArrowDown() {}
		virtual void onArrowLeft() {}
		virtual void onArrowRight() {}
		virtual void onArrowUp() {}
		virtual void onCopy() {}
		virtual void onEsc() {}
		virtual void onPaste() {}
		virtual void onTab() {}

		virtual void onBackspace() = 0;
		virtual void onEnter() = 0;
		virtual void onTextInput(char* text) = 0;
	};
}