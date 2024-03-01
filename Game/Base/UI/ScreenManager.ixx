export module fbc.screenManager;

import fbc.baseScreen;
import fbc.futil;
import fbc.hitbox;
import fbc.uiBase;

deque<fbc::baseScreen::BaseScreen*> screens;
deque<fbc::cpt::UIBase*> overlays;
fbc::hitbox::Hitbox* lastClicked;

export namespace fbc::screenManager {

	// Clear the screen of overlays
	void closeAllOverlays() {
		for (fbc::cpt::UIBase* overlay : overlays) {
			overlay->close();
		}
		overlays.clear();
	}

	// Close the currently opened screen and reopen the last screen opened
	void closeCurrentScreen() {
		if (!screens.empty()) {
			fbc::baseScreen::BaseScreen* screen = screens.front();
			screen->close();
			closeAllOverlays();
			if (!screens.empty()) {
				screens.front()->open();
			}
		}
	}

	// Close a specific overlay and all overlays above it
	void closeOverlay(fbc::cpt::UIBase* target) {
		while (!overlays.empty() && overlays.front() != target) {
			fbc::cpt::UIBase* overlay = overlays.front();
			overlay->close();
			overlays.pop_front();
		}
	}

	// Dispose all screens and their objects
	void dispose() {

	}

	// Add an overlay to the top of the screen
	void openOverlay(fbc::cpt::UIBase* target) {
		overlays.push_front(target);
	}

	// Add a screen to the history of opened screens and open that screen
	void openScreen(fbc::baseScreen::BaseScreen* screen) {
		closeAllOverlays();
		screens.push_front(screen);
		screen->open();
	}

	void render() {
		if (!screens.empty()) {
			screens.front()->render();
		}
		for (fbc::cpt::UIBase* overlay : overlays) {
			overlay->render();
		}
	}

	// Close the current screen and switch the specified screen
	void swapScreen(fbc::baseScreen::BaseScreen* screen) {
		if (!screens.empty()) {
			fbc::baseScreen::BaseScreen* screen = screens.front();
			screen->close();
		}
		openScreen(screen);
	}

	// Helper method to ensure that only one button is clicked at a time
	bool tryClick(fbc::hitbox::Hitbox* hb) {
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