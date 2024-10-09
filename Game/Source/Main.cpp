import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.ConfigHotkey;
import fbc.DynamicContent;
import fbc.FUtil;
import fbc.FWindow;
import fbc.TitleScreen;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

using namespace fbc;

int main()
{
	if (!sdl::runner::init()) {
		return -1;
	}

	CoreConfig cfg = CoreConfig(fbc::futil::FBC);
	cfg.fullLoad();
	CoreContent cct = DynamicContent::generate(cfg, fbc::futil::FBC);

	FWindow window = FWindow(cct);
	window.openScreen(std::make_unique<fbc::TitleScreen>(window, cct));

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
