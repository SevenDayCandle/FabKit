export module fbc.baseScreen;

export namespace fbc::baseScreen {
	export class BaseScreen {
	public:
		virtual void close();
		virtual void dispose();
		virtual void open();
		virtual void render();
		virtual void update();
	};
}