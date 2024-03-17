import fbc.coreConfig;
import fbc.screenManager;
import fbc.titleScreen;
import raylib;

void dispose() {
	// TODO save game state as necessary
}

void draw() {
	raylib::beginDrawing();
	raylib::clearBackground(raylib::White);

	fbc::screenManager::render();

	raylib::endDrawing();
}

void update() {
	fbc::screenManager::update();
}

void initialize() {
	fbc::initializeCfg();
	fbc::screenManager::openScreen(std::make_unique<fbc::TitleScreen>());
}

int main()
{
	raylib::setExitKey(raylib::KeyboardKey::KEY_NULL); // Don't close the game when esc is pressed

	initialize();

	while(!raylib::windowShouldClose())
	{
		update();
		draw();
	}

	dispose();

	raylib::closeWindow();
}
