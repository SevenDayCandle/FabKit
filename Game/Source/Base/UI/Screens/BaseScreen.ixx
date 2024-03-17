export module fbc.baseScreen;

export namespace fbc {
	export class BaseScreen {
	public:
		virtual ~BaseScreen() {}

		virtual void close() = 0; // Called when the screen is destroyed
		virtual void open() = 0; // Called when the screen is first opened or reopened after a screen above it is closed
		virtual void render() = 0;
		virtual void update() = 0;
	};
}