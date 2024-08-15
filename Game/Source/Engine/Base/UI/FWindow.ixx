export module fbc.FWindow;

import fbc.FUtil;
import fbc.UIBase;
import fbc.IOverlay;
import sdl;
import std;

namespace fbc {
	export class FWindow {
	public:
		class Element {
			Element(FWindow& window): window(window) {}

			FWindow& window;

			inline virtual void dispose() {};
			inline virtual void open() {}
			inline virtual void refreshDimensions() {}  // Force resizing of hitboxes when the screen size changes

			virtual bool tickUpdate();

			virtual void render(sdl::GpuCommandBuffer* cd, sdl::GpuRenderPass* rp) = 0;
			virtual void update() = 0;
		};

		FWindow() {}

		UIBase* activeElement;

		bool hasOverlay(IOverlay* target);
		IOverlay* getActiveOverlay();
		UIBase* currentScreen();
		void closeCurrentScreen();
		void closeOverlay(IOverlay* target);
		void dispose();
		void openOverlay(std::unique_ptr<IOverlay>&& target);
		void openScreen(std::unique_ptr<UIBase>&& screen);
		void queueTip(IOverlay* tip);
		void refreshSize();
		void render();
		void subscribeToConfig();
		void swapScreen(std::unique_ptr<UIBase>&& screen);
		void update();
	private:
		bool enabled;
		const uint8* key;
		const uint8* pad;
		deque<uptr<UIBase>> screens;
		deque<uptr<IOverlay>> overlays;
		int mouse = -1;
		int mouseLast = -1;
		int mousePosX = 0;
		int mousePosY = 0;
		int mouseWheelX = 0;
		int mouseWheelY = 0;
		int numKeys;
		int numPads;
		IOverlay* queuedCloseOverlay;
		IOverlay* tipBatch;
		bool queuedCloseScreen;
		int z;
	};
}