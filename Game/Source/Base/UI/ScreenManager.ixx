export module fbc.screenManager;

import fbc.baseScreen;
import fbc.futil;
import fbc.hitbox;
import fbc.uiBase;

deque<uptr<fbc::BaseScreen>> screens;
deque<fbc::UIBase*> overlays;
fbc::Hitbox* lastClicked;

export namespace fbc::screenManager {

	// Clear the screen of overlays
	void closeAllOverlays() {
		for (fbc::UIBase* overlay : overlays) {
			overlay->close();
		}
		overlays.clear();
	}

	// Close the currently opened screen and reopen the last screen opened.
	// The screen's close method should save any screen state as necessary since the screen will get disposed of
	void closeCurrentScreen() {
		if (!screens.empty()) {
			fbc::BaseScreen& screen = *screens.front();
			screen.close();
			screens.pop_front();
			closeAllOverlays();
			if (!screens.empty()) {
				screens.front()->open();
			}
		}
	}

	// Close a specific overlay and all overlays above it
	void closeOverlay(fbc::UIBase* target) {
		while (!overlays.empty() && overlays.front() != target) {
			fbc::UIBase* overlay = overlays.front();
			overlay->close();
			overlays.pop_front();
		}
	}

	// Add an overlay to the top of the screen
	void openOverlay(fbc::UIBase* target) {
		overlays.push_front(target);
	}

	// Add a screen to the history of opened screens and open that screen
	void openScreen(uptr<fbc::BaseScreen> screen) {
		closeAllOverlays();
		screens.push_front(std::move(screen));
		screens.front()->open();
	}

	void render() {
		if (!screens.empty()) {
			screens.front()->render();
		}
		for (fbc::UIBase* overlay : overlays) {
			overlay->render();
		}
	}

	// Close the current screen and switch the specified screen
	void swapScreen(uptr<fbc::BaseScreen> screen) {
		if (!screens.empty()) {
			fbc::BaseScreen& screenFront = *screens.front();
			screenFront.close();
		}
		closeAllOverlays();
		screens.push_front(std::move(screen));
		screens.front()->open();
	}

	// Helper method to ensure that only one button is clicked at a time
	bool tryClick(fbc::Hitbox* hb) {
		if (lastClicked == nullptr || lastClicked == hb) {
			lastClicked = hb;
			return true;
		}
		return false;
	}

	void update() {
		if (!overlays.empty()) {
			overlays.front()->update();
		}
		else if (!screens.empty()) {
			screens.front()->update();
		}
		lastClicked = nullptr;
	}
}