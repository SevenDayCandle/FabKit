import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.ConfigHotkey;
import fbc.DynamicContent;
import fbc.FWindow;
import fbc.TitleScreen;
import sdl;
import std;

using namespace fbc;

FWindow window;

void dispose() {
	// TODO save game state as necessary
	window.dispose();
	cct.dispose();
	sdl::runner::quit();
}

bool initialize() {
	if (!sdl::runner::init()) {
		return false;
	}

	cfg.load();
	fbc::Hotkey::reload();
	cfg.postInitialize();
	cct.initialize();
	DynamicContent::loadDynamicContent();
	cct.initializeContents();
	cct.postInitialize();

	window.subscribeToCore(cfg);
	window.openScreen(std::make_unique<fbc::TitleScreen>(window));
	return true;
}

int main()
{
	if (!initialize()) {
		return -1;
	}

	while(sdl::runner::poll())
	{
		window.update();
		window.render();
		
		// Only limit frame if vsync is off
		if (!cfg.graphicsVSync.get()) {
			sdl::runner::capFrame();
		}
	}

	dispose();
	return 0;
}
