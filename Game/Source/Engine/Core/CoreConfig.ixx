export module fbc.CoreConfig;

import fbc.Config;
import fbc.ConfigHotkey;
import fbc.ConfigValue;
import fbc.ConfigNumeric;
import fbc.FUtil;
import fbc.Language;
import fbc.WindowMode;
import sdl;
import std;

namespace fbc {
	export constexpr float BASE_DENOMINATOR = 2160;
	export constexpr float VOLUME_SCALAR = .0128;
	export constexpr ilist<pair<int, int>> RESOLUTIONS = {
		{320, 240},
		{640, 480},
		{800, 600},
		{1024, 600},
		{1024, 768},
		{1152, 864},
		{1280, 720},
		{1280, 768},
		{1280, 800},
		{1360, 768},
		{1366, 768},
		{1440, 900},
		{1536, 864},
		{1600, 900},
		{1680, 1050},
		{1920, 1080},
		{1920, 1200},
		{2048, 1152},
		{2560, 1080},
		{2560, 1440},
		{2560, 1600},
		{2880, 1800},
		{3440, 1440},
		{3840, 1600},
		{3840, 2160},
	};
	export constexpr strv FONT_BOLD = "Resources/Fonts/NotoSans-Bold.ttf";
	export constexpr strv FONT_REGULAR = "Resources/Fonts/NotoSans-Regular.ttf";

	export class CoreConfig : public Config {
	public:
		CoreConfig(strv id) : Config(id) {}

		ConfigValue<bool> graphicsParticleEffects = ConfigValue<bool>(*this, "GraphicsParticleEffects", true);
		ConfigValue<bool> graphicsVSync = ConfigValue<bool>(*this, "GraphicsVSync", true);
		ConfigValue<bool> textIcons = ConfigValue<bool>(*this, "TextIcons", false);
		ConfigValue<pair<int, int>> graphicsResolution = ConfigValue<pair<int,int>>(*this, "GraphicsResolution", {1920, 1080});
		ConfigValue<str> textFont = ConfigValue<str>(*this, "TextFont", str(FONT_REGULAR));
		ConfigValue<str> textFontBold = ConfigValue<str>(*this, "TextFontBold", str(FONT_BOLD));
		ConfigValue<str> textLanguage = ConfigValue<str>(*this, "TextLanguage", str(lang::ENG_DEFAULT));
		ConfigValue<WindowMode> graphicsWindowMode = ConfigValue<WindowMode>(*this, "GraphicsWindowMode", WindowMode::WINDOWED);
		ConfigNumeric gameActionSpeed = ConfigNumeric(*this, "GameActionSpeed", 3, 1, 5);
		ConfigNumeric graphicsFPS = ConfigNumeric(*this, "GraphicsFPS", 144, 30, 240);
		ConfigNumeric soundVolumeEffects = ConfigNumeric(*this, "SoundVolumeEffects", 100, 0, 100);
		ConfigNumeric soundVolumeMaster = ConfigNumeric(*this, "SoundVolumeMaster", 100, 0, 100);
		ConfigNumeric soundVolumeMusic = ConfigNumeric(*this, "SoundVolumeMusic", 100, 0, 100);
		ConfigNumeric textFontScale = ConfigNumeric(*this, "TextFontScale", 1, 1, 4);

		Hotkey actDirDown = Hotkey::add("ActDirDown", sdl::SCAN_DOWN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_DOWN);
		Hotkey actDirLeft = Hotkey::add("ActDirLeft", sdl::SCAN_LEFT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_LEFT);
		Hotkey actDirRight = Hotkey::add("ActDirRight", sdl::SCAN_RIGHT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
		Hotkey actDirUp = Hotkey::add("ActDirUp", sdl::SCAN_UP, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_UP);
		Hotkey actEsc = Hotkey::add("ActEsc", sdl::SCAN_ESC, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_INVALID);
		Hotkey actSelect = Hotkey::add("ActSelect", sdl::SCAN_RETURN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_START);

		inline int getScreenXSize() { return graphicsResolution.get().first; }
		inline int getScreenYSize() { return graphicsResolution.get().second; };
		inline float fontScale() const noexcept { return fontScalePrivate; } // Gets the scale factor to setExactSize fonts by. Resolution uses the height of a 4k screen as a base
		inline float fontScale(float mult) const noexcept { return fontScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.
		inline float renderScale() const noexcept { return renderScalePrivate; } // Gets the scale factor to setExactSize elements by. Resolution uses the height of a 4k screen as a base
		inline float renderScale(float mult) const noexcept { return renderScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.

		const Language& getLanguage();

		void postInitialize() override;
		void resizeWindow();
		void setupWindow();
		void updateWindowMode();
	private:
		float fontScalePrivate = 1.0;
		float renderScalePrivate = 1.0;

		void updateScales();
	};

	export CoreConfig cfg = CoreConfig(futil::FBC);

	// Get the game language, defaulting to English if it is invalid
	const Language& CoreConfig::getLanguage() {
		try {
			return Language::forceGet(textLanguage.get());
		}
		catch (exception e) {
			sdl::logError("Language failed to load: %s. Defaulting to ENG", e);
		}
		return lang::ENG;
	}

	void CoreConfig::postInitialize() {
		updateScales();
		sdl::musicSetVolume(soundVolumeMusic.get() * soundVolumeMaster.get() * VOLUME_SCALAR);
		sdl::soundSetAllVolume(soundVolumeEffects.get() * soundVolumeMaster.get() * VOLUME_SCALAR);

		// Add sound config subscriptions. Note that graphical config subscriptions need to get set up in screenManager since they invoke refreshing on the screenManager
		soundVolumeMaster.setOnReload([this](const int& val) {
			sdl::musicSetVolume(soundVolumeMusic.get() * val * VOLUME_SCALAR);
			sdl::soundSetAllVolume(soundVolumeEffects.get() * val * VOLUME_SCALAR);
		});
		soundVolumeEffects.setOnReload([this](const int& val) {
			sdl::soundSetAllVolume(val * soundVolumeMaster.get() * VOLUME_SCALAR);
		});
		soundVolumeMusic.setOnReload([this](const int& val) {
			sdl::musicSetVolume(val * soundVolumeMaster.get() * VOLUME_SCALAR);
		});
	}

	// When the window size parameters change, we should setExactSize the window and update renderScalePrivate
	void CoreConfig::resizeWindow()
	{
		sdl::windowSetSize(getScreenXSize(), getScreenYSize());
		updateScales();
	}

	// Create the window from the config
	void CoreConfig::setupWindow() {
		sdl::initWindow(getScreenXSize(), getScreenYSize(), graphicsWindowMode.get(), graphicsVSync.get());
	}

	// Update the window fullscreen mode from the config
	void CoreConfig::updateWindowMode() {
		switch (graphicsWindowMode.get()) {
		case BORDERLESS_FULLSCREEN:
			sdl::windowSetFullscreen(1);
			break;
		case FULLSCREEN:
			sdl::windowSetFullscreen(1);
			break;
		default:
			sdl::windowSetFullscreen(0);
			break;
		}
	}

	// Resolution uses the height of a 4k screen as a base
	void CoreConfig::updateScales()
	{
		renderScalePrivate = getScreenYSize() / BASE_DENOMINATOR;
		fontScalePrivate = renderScalePrivate * textFontScale.get();
	}
}