import fbc;
import raylib;


int main()
{
	raylib::setExitKey(raylib::KeyboardKey::KEY_NULL); // Don't close the game when esc is pressed

	fbc::initialize();

	while(!raylib::windowShouldClose())
	{
		fbc::update();
		fbc::draw();
	}

	fbc::dispose();

	raylib::closeWindow();
}