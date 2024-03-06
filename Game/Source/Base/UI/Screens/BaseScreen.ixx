export module fbc.baseScreen;

import fbc.screenHitbox;
import fbc.uiCanvas;

export namespace fbc::ui {
	export class BaseScreen {
	public:
		virtual ~BaseScreen() {}

		UICanvas canvas;

		virtual void close();
		virtual void dispose();
		virtual void open();
		virtual void render();
		virtual void update();
	};
}