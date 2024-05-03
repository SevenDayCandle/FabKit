export module sdl.iKeyInputListener;


export namespace sdl {
	export class IKeyInputListener {
	public:
		IKeyInputListener() {}
		virtual ~IKeyInputListener() {}

		virtual void onArrowDown() {}
		virtual void onArrowLeft() {}
		virtual void onArrowRight() {}
		virtual void onArrowUp() {}
		virtual void onBackspace() {};
		virtual void onCopy() {}
		virtual void onEnter() {};
		virtual void onEsc() {}
		virtual void onPaste() {}
		virtual void onTab() {}

		virtual void onTextInput(char* text) = 0;
	};
}