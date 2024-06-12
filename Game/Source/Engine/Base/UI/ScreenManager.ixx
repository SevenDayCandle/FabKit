export module fbc.ScreenManager;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import fbc.UIBase;
import sdl;
import std;

namespace fbc {
	fbc::deque<fbc::uptr<fbc::UIBase>> screens;
	fbc::deque<fbc::uptr<fbc::IOverlay>> overlays;
	fbc::IOverlay* queuedCloseOverlay;
	bool queuedCloseScreen;
}

export namespace fbc::screenManager {
	fbc::UIBase* activeElement;

	// Close the currently opened screen and reopen the last screen opened.
	// The screen's dispose method should save any screen state as necessary since the screen will get disposed of
	// Note that the screen will dispose at the END of the update cycle to ensure that all screen logic for the loop is executed
	void closeCurrentScreen() {
		queuedCloseScreen = true;
	}

	// Close a specific overlay and all overlays above it
	// Note that the overlay will dispose at the END of the update cycle to ensure that all overlay logic for the loop is executed
	void closeOverlay(fbc::IOverlay* target) {
		queuedCloseOverlay = target;
	}

	// Destroy all screens and overlays
	void dispose() {
		overlays.clear();
		screens.clear();
	}

	// Get the active overlay
	IOverlay* getActiveOverlay() {
		if (overlays.empty()) {
			return nullptr;
		}
		return overlays.back().get();
	}

	// Add an overlay to the top of the screen
	void openOverlay(uptr<fbc::IOverlay>&& target) {
		overlays.push_back(std::move(target));
	}

	// Add a screen to the history of opened screens and open that screen. Also dispose all overlays
	void openScreen(uptr<fbc::UIBase>&& screen) {
		screens.push_back(std::move(screen));
		screens.back()->open();
		if (!overlays.empty()) {
			closeOverlay(overlays.front().get());
		}
		activeElement = nullptr;
		sdl::keyboardInputStop();
	}

	// Whenever the screen size changes, we need to setExactSize all UI elements
	void refreshSize() {
		for (const uptr<UIBase>& screen : screens) {
			screen->refreshDimensions();
		}
		for (const uptr<IOverlay>& overlay : overlays) {
			overlay->refreshDimensions();
		}
	}

	// Render the last opened screen, as well as all overlays
	void render() {
		if (!screens.empty()) {
			screens.back()->renderImpl();
		}
		for (const uptr<IOverlay>& overlay : overlays) {
			overlay->render();
		}
	}

	// Close the current screen and switch the specified screen. Also dispose all overlays
	void swapScreen(uptr<fbc::UIBase>&& screen) {
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
		sdl::keyboardInputStop();
	}

	// Update the last opened overlay if it exists, otherwise update the last opened screen
	void update() {
		if (!overlays.empty()) {
			overlays.back()->update();
		}
		else if (!screens.empty()) {
			screens.back()->updateImpl();
		}

		// Check if currently opened should dispose. If so, dispose all overlays and the screen, then reopen the last screen
		if (queuedCloseScreen) {
			if (!screens.empty()) {
				fbc::UIBase& screen = *screens.back();
				screen.dispose();
				screens.pop_back();
				for (const uptr<IOverlay>& overlay : overlays) {
					overlay->dispose();
				}
				overlays.clear();
				if (!screens.empty()) {
					screens.back()->open();
				}
			}
			activeElement = nullptr;
			sdl::keyboardInputStop();
			queuedCloseOverlay = nullptr;
			queuedCloseScreen = false;
		}
		// Otherwise check if there is an overlay to be closed
		else if (queuedCloseOverlay) {
			while (!overlays.empty()) {
				fbc::IOverlay* overlay = overlays.back().get();
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
	void subscribeToConfig() {
		cfg.graphicsResolution.setOnReload([](const pair<int, int>& val) {
			cfg.resizeWindow();
			cct.reloadFonts();
			refreshSize();
		});
		cfg.graphicsWindowMode.setOnReload([](const int& val) {sdl::windowSetFullscreen(val); });
		cfg.graphicsVSync.setOnReload([](const int& val) { sdl::updateVSync(val); });
	}
}