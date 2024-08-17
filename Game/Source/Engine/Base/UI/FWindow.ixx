export module fbc.FWindow;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.IDrawable;
import sdl;
import sdl.IKeyInputListener;
import std;

namespace fbc {
	export class FWindow {
	public:
		class Element {
		public:
			Element(FWindow& window): win(window) {}
			virtual ~Element() = default;

			FWindow& win;

			inline virtual void dispose() {};
			inline virtual void open() {}
			inline virtual void renderImpl(sdl::SDLBatchRenderPass& rp) { render(rp); } // 
			inline virtual void refreshDimensions() {}  // Force resizing of hitboxes when the screen size changes
			inline virtual void updateImpl() { update(); }

			virtual bool tickUpdate();

			virtual void render(sdl::SDLBatchRenderPass& rp) = 0;
			virtual void update() = 0;
		};

		FWindow() {}

		Element* activeElement;

		inline int getH() const noexcept { return winH; }
		inline int getW() const noexcept { return winW; }
		inline void keyboardInputStopRequest(sdl::IKeyInputListener* listener) { sdl::runner::keyboardInputStopRequest(window, listener); }
		inline void keyboardInputStart(sdl::IKeyInputListener* listener) { sdl::runner::keyboardInputStart(window, listener); }

		bool hasOverlay(Element* target);
		bool initialize(int w, int h, uint32 windowFlags = 0, bool vsync = false, const char* title = "Fabricate");
		Element* getActiveOverlay();
		Element* currentScreen();
		void closeCurrentScreen();
		void closeOverlay(Element* target);
		void dispose();
		void openOverlay(uptr<Element>&& target);
		void openScreen(uptr<Element>&& screen);
		void queueTip(Element* tip);
		void refreshSize(int winW, int winH);
		void render();
		void subscribeToCore(CoreConfig& cfg);
		void swapScreen(uptr<Element>&& screen);
		void update();
	private:
		bool enabled;
		bool queuedCloseScreen;
		deque<uptr<Element>> screens;
		deque<uptr<Element>> overlays;
		Element* queuedCloseOverlay;
		Element* tipBatch;
		sdl::Matrix4x4 matrixUniform = {
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		sdl::Window* window;
		int winH;
		int winW;
		int z;
	};

	// Set up window and its rendering device. Returns true if set up successfully
	bool FWindow::initialize(int w, int h, uint32 windowFlags, bool vsync, const char* title)
	{
		this->winH = h;
		this->winW = w;
		window = sdl::windowCreate(title, w, h, windowFlags);
		if (!window) {
			sdl::logCritical("Window went derp: %s", sdl::getError());
			return false;
		}

		// Setup device for this window
		if (!sdl::runner::deviceClaimWindow(window, sdl::GpuSwapchainComposition::SDL_GPU_SWAPCHAINCOMPOSITION_SDR, vsync ? sdl::GpuPresentMode::SDL_GPU_PRESENTMODE_VSYNC : sdl::GpuPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE))
		{
			sdl::logCritical("GpuClaimWindow went derp: %s", sdl::getError());
			return false;
		}

		return true;
	}

	// Close the currently opened screen and reopen the last screen opened.
	// The screen's dispose method should save any screen state as necessary since the screen will get disposed of
	// Note that the screen will dispose at the END of the update cycle to ensure that all screen logic for the loop is executed
	void FWindow::closeCurrentScreen() {
		queuedCloseScreen = true;
	}

	// Get the currently opened screen
	FWindow::Element* FWindow::currentScreen() {
		return screens.empty() ? nullptr : screens.back().get();
	}

	// Close a specific overlay and all overlays above it
	// Note that the overlay will dispose at the END of the update cycle to ensure that all overlay logic for the loop is executed
	void FWindow::closeOverlay(Element* target) {
		queuedCloseOverlay = target;
	}

	// Destroy all resources
	void FWindow::dispose() {
		overlays.clear();
		screens.clear();

		sdl::runner::deviceUnclaimWindow(window);
		sdl::windowDestroy(window);
		window = nullptr;
	}

	// Check if a given overlay is present
	bool FWindow::hasOverlay(Element* target)
	{
		return std::ranges::any_of(overlays, [target](uptr<Element>& o) {return o.get() == target; });
	}

	// Get the active overlay
	FWindow::Element* FWindow::getActiveOverlay() {
		if (overlays.empty()) {
			return nullptr;
		}
		return overlays.back().get();
	}

	// Add an overlay to the top of the screen. The screen manager will take ownership of this overlay.
	void FWindow::openOverlay(uptr<FWindow::Element>&& target) {
		overlays.push_back(std::move(target));
	}

	// Add a screen to the history of opened screens and open that screen. The screen manager will take ownership of this screen. Also dispose all overlays and tooltips.
	void FWindow::openScreen(uptr<FWindow::Element>&& screen) {
		screens.push_back(std::move(screen));
		screens.back()->open();
		if (!overlays.empty()) {
			closeOverlay(overlays.front().get());
		}
		activeElement = nullptr;
		sdl::runner::keyboardInputStop(window);
	}

	// Add a tooltip batch to be shown. Only one tooltip batch can be shown at a time
	void FWindow::queueTip(Element* tip) {
		if (!tipBatch) {
			tipBatch = tip;
			tipBatch->open();
		}
	}

	// Whenever the screen size changes, we need to setRealSize all UI elements
	void FWindow::refreshSize(int winW, int winH) {
		sdl::windowSetSize(window, winW, winH);
		for (const uptr<FWindow::Element>& screen : screens) {
			screen->refreshDimensions();
		}
		for (const uptr<Element>& overlay : overlays) {
			overlay->refreshDimensions();
		}
	}

	// Render the last opened screen, as well as all overlays
	void FWindow::render() {
		sdl::GpuCommandBuffer* cd = sdl::runner::deviceAcquireCommandBuffer();
		if (cd) {
			uint32 w, h;
			sdl::GpuTexture* swapchain = sdl::gpuAcquireSwapchainTexture(cd, window, &w, &h);
			if (swapchain) {
				sdl::GpuColorAttachmentInfo colorAttachmentInfo = {
					.textureSlice = {
						.texture = swapchain
					},
					.clearColor = { 0.0f, 0.0f, 0.0f, 1.0f },
					.loadOp = sdl::GpuLoadOp::SDL_GPU_LOADOP_CLEAR,
					.storeOp = sdl::GpuStoreOp::SDL_GPU_STOREOP_STORE
				};

				sdl::GpuRenderPass* r = sdl::gpuBeginRenderPass(cd, &colorAttachmentInfo, 1, nullptr);
				sdl::SDLBatchRenderPass rp = sdl::SDLBatchRenderPass(cd, r);
				// Render screen elements
				// TODO pass in z index
				if (!screens.empty()) {
					screens.back()->renderImpl(rp);
				}
				for (const uptr<Element>& overlay : overlays) {
					overlay->render(rp);
				}
				if (tipBatch) {
					tipBatch->render(rp);
				}
				tipBatch = nullptr;
			}

			sdl::gpuSubmit(cd);
		}

	}

	// Close the current screen and switch the specified screen. Also dispose all overlays
	void FWindow::swapScreen(uptr<FWindow::Element>&& screen) {
		// Place the screen to be swapped to right behind the last screen and then queue a dispose, ensuring proper disposal of screens. This also handles opening of the enxt screen
		if (screens.size() >= 2) {
			queuedCloseScreen = true;
			screens.insert(screens.end() - 2, std::move(screen));
		}
		else if (!screens.empty()) {
			queuedCloseScreen = true;
			screens.push_front(std::move(screen));
		}
		else {
			screens.push_back(std::move(screen));
			screens.back()->open();
			if (!overlays.empty()) {
				closeOverlay(overlays.front().get());
			}
		}

		activeElement = nullptr;
		sdl::runner::keyboardInputStop(window);
	}

	// Update the last opened overlay if it exists, otherwise update the last opened screen
	void FWindow::update() {
		if (!overlays.empty()) {
			overlays.back()->update();
		}
		else if (!screens.empty()) {
			screens.back()->updateImpl();
		}
		if (tipBatch) {
			tipBatch->update();
		}

		// Check if currently opened should dispose. If so, dispose all overlays and the screen, then reopen the last screen
		if (queuedCloseScreen) {
			if (!screens.empty()) {
				Element& screen = *screens.back();
				screen.dispose();
				screens.pop_back();
				for (const uptr<Element>& overlay : overlays) {
					overlay->dispose();
				}
				overlays.clear();
				if (!screens.empty()) {
					screens.back()->open();
				}
			}
			activeElement = nullptr;
			sdl::runner::keyboardInputStop(window);
			queuedCloseOverlay = nullptr;
			queuedCloseScreen = false;
		}
		// Otherwise check if there is an overlay to be closed
		else if (queuedCloseOverlay) {
			while (!overlays.empty()) {
				FWindow::Element* overlay = overlays.back().get();
				overlay->dispose();
				overlays.pop_back();
				if (overlay == queuedCloseOverlay) {
					break;
				}
			}
			queuedCloseOverlay = nullptr;
		}
	}

	// Attach listeners to the core config to change the screen whenever graphics settings are changed
	void FWindow::subscribeToCore(CoreConfig& cfg) {
		const pair<int, int>& resolution = cfg.graphicsResolution.get();
		initialize(resolution.first, resolution.second, cfg.graphicsWindowMode.get(), cfg.graphicsVSync.get());

		cfg.graphicsResolution.addOnReload([this](const pair<int, int>& val) {refreshSize(val.first, val.second);});
		cfg.graphicsWindowMode.addOnReload([this](const int& val) {sdl::windowSetFullscreen(window, val); });
		cfg.graphicsVSync.addOnReload([this](const bool& val) { sdl::runner::deviceSetSwapchainParameters(window, sdl::GpuSwapchainComposition::SDL_GPU_SWAPCHAINCOMPOSITION_SDR, val ? sdl::GpuPresentMode::SDL_GPU_PRESENTMODE_VSYNC : sdl::GpuPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE); });
	}

	bool FWindow::Element::tickUpdate()
	{
		update();
		return true;
	}
}