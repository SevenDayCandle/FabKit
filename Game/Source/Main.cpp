import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.ConfigHotkey;
import fbc.DynamicContent;
import fbc.FWindow;
import fbc.TitleScreen;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

using namespace fbc;

int main()
{
	if (!sdl::runner::init()) {
		return -1;
	}

	cfg.load();
	fbc::Hotkey::reload();
	cfg.postInitialize();
	cct.initialize();
	DynamicContent::loadDynamicContent();
	cct.initializeContents();
	cct.postInitialize();

	FWindow window(cfg, cct, "Fabricate");
	window.openScreen(std::make_unique<fbc::TitleScreen>(window));

	while(sdl::runner::poll())
	{
		window.update();
		window.render();
		
		// Only limit frame if vsync is off
		if (!cfg.graphicsVSync.get()) {
			sdl::runner::capFrame();
		}
	}

	window.dispose();
	cct.dispose();
	sdl::runner::quit();
	return 0;
}
