export module fab.FWindow;

import fab.BatchRenderPass;
import fab.EmptyDrawable;
import fab.FFont;
import fab.FSound;
import fab.FUtil;
import fab.IDrawable;
import fab.WindowMode;
import sdl.IKeyInputListener;
import sdl.SDLBase;
import sdl.SDLRunner;
import std;

/* Represents an application window. A wrapper around SDL's window that manages the rendering and lifecycle of screens to be rendered in that window */
namespace fab {
	export class FWindow {
	public:
		/* An element that can be placed into a FWindow */
		class Element {
		public:
			Element(FWindow& window): win(window) {}
			virtual ~Element() = default;

			FWindow& win;

			inline virtual void dispose() {} // Should be called when this element is destroyed
			inline virtual void open() {} // Should be called when this element is added to a window
			inline virtual void renderImpl(BatchRenderPass& rp) { render(rp); } // 
			inline virtual void refreshDimensions() {} // Force resizing of hitboxes when the screen size changes
			inline virtual void updateImpl() { update(); }

			template <c_ext<Element> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...>
			uptr<T> inline create(Args&&... args) { return make_unique<T>(win, forward<Args>(args)...); } // Generate a component using this element's window

			virtual void render(BatchRenderPass& rp) = 0;
			virtual void update() = 0;
		};

		/* Properties that dictate how this window should be set up */
		struct IController {
			IController() {}
			virtual ~IController() = default;

			virtual inline bool getVsync() { return true; }
			virtual inline bool hasPressedClose() { return false; }
			virtual inline bool hasPressedDirDown() { return false; }
			virtual inline bool hasPressedDirUp() { return false; }
			virtual inline bool hasPressedSelect() { return false; }
			virtual inline FFont& fontBold() const { return fontRegular(); }
			virtual inline FFont& fontSmall() const { return fontRegular(); }
			virtual inline FSound* defaultClick() { return nullptr; }
			virtual inline IDrawable& defaultArrow() { return EMPTY; }
			virtual inline IDrawable& defaultArrowSmall() { return defaultArrow(); }
			virtual inline IDrawable& defaultBackground() { return EMPTY; }
			virtual inline IDrawable& defaultButton() { return EMPTY; }
			virtual inline IDrawable& defaultCheckboxEmpty() { return EMPTY; }
			virtual inline IDrawable& defaultCheckboxFilled() { return EMPTY; }
			virtual inline IDrawable& defaultClear() { return EMPTY; }
			virtual inline IDrawable& defaultPanel() { return EMPTY; }
			virtual inline IDrawable& defaultScrollBack() { return EMPTY; }
			virtual inline IDrawable& defaultScrollButton() { return EMPTY; }
			virtual inline IDrawable& defaultSlider() { return EMPTY; }
			virtual inline int effectSpeed() const noexcept { return 1; }
			virtual inline void onWindowInitialize(FWindow& window) {}
			virtual inline WindowMode getWindowMode() const { return WINDOWED; }

			virtual const char* getTitle() = 0;
			virtual FFont& fontRegular() const = 0;
			virtual float fontScale() const noexcept = 0;
			virtual float renderScale() const noexcept = 0;
			virtual int getResolutionX() const noexcept = 0;
			virtual int getResolutionY() const noexcept = 0;
		};

		FWindow(IController& props) : props(props) {}
		virtual ~FWindow() = default;

		Element* activeElement;
		IController& props;

		inline float fontScale() const noexcept { return props.fontScale(); }
		inline float fontScale(float mult) const noexcept { return fontScale() * mult; }
		inline float renderScale() const noexcept { return props.renderScale(); }
		inline float renderScale(float mult) const noexcept { return renderScale() * mult; }
		inline int getH() const noexcept { return winH; }
		inline int getW() const noexcept { return winW; }
		inline int effectSpeed() const noexcept { return props.effectSpeed(); }
		inline sdl::Window* sdlWindow() const noexcept { return window; }
		inline void keyboardInputStopRequest(sdl::IKeyInputListener* listener) { sdl::runner::keyboardInputStopRequest(window, listener); }
		inline void keyboardInputStart(sdl::IKeyInputListener* listener) { sdl::runner::keyboardInputStart(window, listener); }

		template <c_ext<FWindow::Element> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...>
		inline T& openNewOverlay(Args&&... args) { return openOverlay(make_unique<T>(*this, forward<Args>(args)...)); };

		template <c_ext<FWindow::Element> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...>
		inline T& openNewScreen(Args&&... args) { return openScreen(make_unique<T>(*this, forward<Args>(args)...)); };

		template <c_ext<FWindow::Element> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...>
		inline T& swapNewScreen(Args&&... args) { return swapScreen(make_unique<T>(*this, forward<Args>(args)...)); };

		template <c_ext<FWindow::Element> T, typename... Args> requires std::constructible_from<T, FWindow&, Args&&...>
		uptr<T> inline create(Args&&... args) { return make_unique<T>(*this, forward<Args>(args)...); } // Generate a component using this window

		bool hasOverlay(Element* target);
		bool initialize();
		FWindow::Element* getActiveOverlay();
		FWindow::Element* currentScreen();
		template <c_ext<FWindow::Element> T> T& openOverlay(uptr<T>&& target);
		template <c_ext<FWindow::Element> T> T& openScreen(uptr<T>&& screen);
		template <c_ext<FWindow::Element> T> T& swapScreen(uptr<T>&& screen);
		void closeCurrentScreen();
		void closeOverlay(Element* target);
		void dispose();
		void queueTip(Element* tip);
		void refreshSize(int winW, int winH);
		void render();
		void update();
	private:
		bool queuedCloseScreen;
		deque<uptr<Element>> screens;
		deque<uptr<Element>> overlays;
		Element* queuedCloseOverlay;
		Element* tipBatch;
		FWindow* parent;
		sdl::Matrix4x4 projection;
		sdl::Window* window;
		int winH;
		int winW;

		static sdl::Matrix4x4 makeProjection(int w, int h);
	};

	// Set up window and its rendering device. Returns true if set up successfully
	bool FWindow::initialize() {
		this->winW = props.getResolutionX();
		this->winH = props.getResolutionY();
		projection = makeProjection(winW, winH);
		// TODO setup projection
		window = sdl::windowCreate(props.getTitle(), winW, winH, props.getWindowMode());
		if (!window) {
			sdl::logCritical("Window went derp: %s", sdl::getError());
			return false;
		}

		// Setup device for this window
		if (!sdl::runner::deviceClaimWindow(window)) {
			sdl::logCritical("GPUClaimWindow went derp: %s", sdl::getError());
			return false;
		}

		sdl::GPUPresentMode presentMode;
		if (props.getVsync() && sdl::runner::deviceSupportsPresentMode(window, sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_VSYNC)) {
			presentMode = sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_VSYNC;
		}
		else if (sdl::runner::deviceSupportsPresentMode(window, sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE)) {
			presentMode = sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE;
		}
		else if (sdl::runner::deviceSupportsPresentMode(window, sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_IMMEDIATE)) {
			presentMode = sdl::GPUPresentMode::SDL_GPU_PRESENTMODE_MAILBOX;
		}
		else {
			sdl::logCritical("No present modes are supported! WTF!");
			return false;
		}

		if (!sdl::runner::deviceSetSwapchainParameters(window, sdl::GPUSwapchainComposition::SDL_GPU_SWAPCHAINCOMPOSITION_SDR, presentMode)) {
			sdl::logCritical("Swapchain went derp: %s", sdl::getError());
			return false;
		}
		props.onWindowInitialize(*this);

		return true;
	}

	// left = 0, right = w, bottom = h, top = 0
	sdl::Matrix4x4 FWindow::makeProjection(int w, int h) {
		return {
			2.0f / w, 0, 0, 0,
			0, 2.0f / -h, 0, 0,
			0, 0, 1.0f, 0,
			-1, 1, 0, 1
		};
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
	bool FWindow::hasOverlay(Element* target) {
		return std::ranges::any_of(overlays, [target](uptr<Element>& o) { return o.get() == target; });
	}

	// Get the active overlay
	FWindow::Element* FWindow::getActiveOverlay() {
		if (overlays.empty()) {
			return nullptr;
		}
		return overlays.back().get();
	}

	// Add an overlay to the top of the screen. The screen manager will take ownership of this overlay.
	template <c_ext<FWindow::Element> T> T& FWindow::openOverlay(uptr<T>&& target) {
		T& ret = *target;
		overlays.push_back(std::move(target));
		return ret;
	}

	// Add a screen to the history of opened screens and open that screen. The screen manager will take ownership of this screen. Also dispose all overlays and tooltips.
	template <c_ext<FWindow::Element> T> T& FWindow::openScreen(uptr<T>&& screen) {
		T& ret = *screen;
		screens.push_back(std::move(screen));
		screens.back()->open();
		if (!overlays.empty()) {
			closeOverlay(overlays.front().get());
		}
		activeElement = nullptr;
		sdl::runner::keyboardInputStop(window);
		return ret;
	}

	// Close the current screen and switch the specified screen. Also dispose all overlays
	template <c_ext<FWindow::Element> T> T& FWindow::swapScreen(uptr<T>&& screen) {
		T& ret = *screen;
		// Place the screen to be swapped to right behind the last screen and then queue a dispose, ensuring proper disposal of screens. This also handles opening of the next screen
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
		return ret;
	}

	// Add a tooltip batch to be shown. Only one tooltip batch can be shown at a time
	void FWindow::queueTip(Element* tip) {
		if (!tipBatch) {
			tipBatch = tip;
			tipBatch->open();
		}
	}

	// Whenever the screen size changes, we need to resize all UI elements
	void FWindow::refreshSize(int winW, int winH) {
		this->winH = winH;
		this->winW = winW;
		projection = makeProjection(winW, winH);
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
		sdl::GPUCommandBuffer* cd = sdl::runner::deviceAcquireCommandBuffer();
		if (cd) {
			uint32 w, h;
			sdl::GPUTexture* swapchain = sdl::gpuAcquireSwapchainTexture(cd, window, &w, &h);
			if (swapchain) {
				sdl::GPUColorTargetInfo colorAttachmentInfo = {
					.texture = swapchain,
					.mip_level = 0,
					.layer_or_depth_plane = 0,
					.clear_color = {0.0f, 0.0f, 0.0f, 1.0f},
					.load_op = sdl::GPULoadOp::SDL_GPU_LOADOP_CLEAR,
					.store_op = sdl::GPUStoreOp::SDL_GPU_STOREOP_STORE
				};

				BatchRenderPass rp = BatchRenderPass(cd, &colorAttachmentInfo, 1, nullptr);
				rp.pushVertexUniform(&projection, sizeof(sdl::Matrix4x4));
				rp.reset();
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
				rp.draw();
			}

			sdl::gpuSubmit(cd);
		}
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
}
