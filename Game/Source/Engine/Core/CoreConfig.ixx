export module fbc.CoreConfig;

import fbc.Config;
import fbc.ConfigHotkey;
import fbc.ConfigValue;
import fbc.ConfigNumeric;
import fbc.FUtil;
import fbc.Language;
import fbc.WindowMode;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
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
		ConfigNumeric gameEffectSpeed = ConfigNumeric(*this, "GameEffectSpeed", 1, 1, 5);
		ConfigNumeric graphicsFPS = ConfigNumeric(*this, "GraphicsFPS", 144, 30, 240);
		ConfigNumeric soundVolumeEffects = ConfigNumeric(*this, "SoundVolumeEffects", 100, 0, 100);
		ConfigNumeric soundVolumeMaster = ConfigNumeric(*this, "SoundVolumeMaster", 100, 0, 100);
		ConfigNumeric soundVolumeMusic = ConfigNumeric(*this, "SoundVolumeMusic", 100, 0, 100);
		ConfigNumeric textFontPercent = ConfigNumeric(*this, "TextFontPercent", 100, 50, 400);

		Hotkey actDirDown = Hotkey("ActDirDown", sdl::SCAN_DOWN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_DOWN);
		Hotkey actDirLeft = Hotkey("ActDirLeft", sdl::SCAN_LEFT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_LEFT);
		Hotkey actDirRight = Hotkey("ActDirRight", sdl::SCAN_RIGHT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
		Hotkey actDirUp = Hotkey("ActDirUp", sdl::SCAN_UP, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_UP);
		Hotkey actEsc = Hotkey("ActEsc", sdl::SCAN_ESC, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_INVALID);
		Hotkey actSelect = Hotkey("ActSelect", sdl::SCAN_RETURN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_START);

		inline float fontScale() const noexcept { return fontScalePrivate; } // Gets the scale factor to setRealSize fonts by. Resolution uses the height of a 4k screen as a base
		inline float fontScale(float mult) const noexcept { return fontScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.
		inline float renderScale() const noexcept { return renderScalePrivate; } // Gets the scale factor to setRealSize elements by. Resolution uses the height of a 4k screen as a base
		inline float renderScale(float mult) const noexcept { return renderScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.

		const Language& getLanguage();

		void postInitialize() override;
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
		sdl::musicSetVolume(soundVolumeMusic.get() * soundVolumeMaster.get() * VOLUME_SCALAR);
		sdl::soundSetAllVolume(soundVolumeEffects.get() * soundVolumeMaster.get() * VOLUME_SCALAR);

		// Add sound config subscriptions
		soundVolumeMaster.addOnReload([this](const int& val) {
			sdl::musicSetVolume(soundVolumeMusic.get() * val * VOLUME_SCALAR);
			sdl::soundSetAllVolume(soundVolumeEffects.get() * val * VOLUME_SCALAR);
		});
		soundVolumeEffects.addOnReload([this](const int& val) {
			sdl::soundSetAllVolume(val * soundVolumeMaster.get() * VOLUME_SCALAR);
		});
		soundVolumeMusic.addOnReload([this](const int& val) {
			sdl::musicSetVolume(val * soundVolumeMaster.get() * VOLUME_SCALAR);
		});

		// Add graphic config subscriptions. Note that most config subscriptions are specific to FWindow
		graphicsFPS.addOnReload([](const int& val) { sdl::runner::setFPSLimit(val); });
		textFontPercent.addOnReload([this](const int& val) { updateScales(); });
	}

	// Resolution uses the height of a 4k screen as a base
	void CoreConfig::updateScales()
	{
		renderScalePrivate = graphicsResolution.get().second / BASE_DENOMINATOR;
		fontScalePrivate = renderScalePrivate * textFontPercent.get() / 100;
	}
}