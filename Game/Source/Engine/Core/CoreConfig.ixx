export module fbc.coreConfig;

import fbc.config;
import fbc.configHotkey;
import fbc.configItem;
import fbc.ffont;
import fbc.futil;
import fbc.language;
import sdl;
import std;

export namespace fbc {
	constexpr float BASE_DENOMINATOR = 2160;

	export class CoreConfig : public Config {
	public:
		CoreConfig(strv ID) : Config(ID) {}
		virtual ~CoreConfig() override {}

		ConfigItem<int> gameActionSpeed = ConfigItem<int>(*this, "GameActionSpeed", 3);
		ConfigItem<bool> graphicsVSync = ConfigItem<bool>(*this, "GraphicsVSync", true);
		ConfigItem<int> graphicsFPS = ConfigItem<int>(*this, "GraphicsFPS", 144);
		ConfigItem<int> graphicsWindowMode = ConfigItem<int>(*this, "GraphicsFPS", 0);
		ConfigItem<bool> graphicsParticleEffects = ConfigItem<bool>(*this, "GraphicsParticleEffects", true);
		ConfigItem<int> graphicsResolutionX = ConfigItem<int>(*this, "GraphicsResolutionX", 1920);
		ConfigItem<int> graphicsResolutionY = ConfigItem<int>(*this, "GraphicsResolutionY", 1080);
		ConfigItem<int> soundVolumeEffects = ConfigItem<int>(*this, "SoundVolumeEffects", 100);
		ConfigItem<int> soundVolumeMaster = ConfigItem<int>(*this, "SoundVolumeMaster", 100);
		ConfigItem<int> soundVolumeMusic = ConfigItem<int>(*this, "SoundVolumeMusic", 100);
		ConfigItem<str> textFont = ConfigItem<str>(*this, "TextFont", FONT_REGULAR);
		ConfigItem<str> textFontBold = ConfigItem<str>(*this, "TextFont", FONT_BOLD);
		ConfigItem<bool> textIcons = ConfigItem<bool>(*this, "TextIcons", false);
		ConfigItem<str> textLanguage = ConfigItem<str>(*this, "TextIcons", lang::ENG);

		Hotkey actDirDown = Hotkey::add("ActDirDown", sdl::KEY_DOWN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_DOWN);
		Hotkey actDirLeft = Hotkey::add("ActDirLeft", sdl::KEY_LEFT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_LEFT);
		Hotkey actDirRight = Hotkey::add("ActDirRight", sdl::KEY_RIGHT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
		Hotkey actDirUp = Hotkey::add("ActDirUp", sdl::KEY_UP, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_UP);
		Hotkey actEsc = Hotkey::add("ActEsc", sdl::KEY_ESC, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_INVALID);

		inline int getScreenXSize() { return graphicsResolutionX.get(); }
		inline int getScreenYSize() { return graphicsResolutionY.get(); };
		inline float renderScale() const noexcept { return renderScalePrivate; }
		inline float renderScale(float mult) const noexcept { return renderScalePrivate * mult; }

		const Language& getLanguage();

		void postInitialize() override;
		void refreshWindow();
	private:
		float renderScalePrivate = 1.0;
	};

	export CoreConfig cfg = CoreConfig(futil::FBC);

	// Get the game language, defaulting to English if it is invalid
	const Language& CoreConfig::getLanguage() {
		try {
			return Language::get(textLanguage.get());
		}
		catch (exception e) {
			sdl::logError("Language failed to load: %s. Defaulting to ENG", e);
		}
		return lang::ENG;
	}

	// Update the window from the config
	void CoreConfig::refreshWindow() {
		sdl::windowSetSize(graphicsResolutionX.get(), graphicsResolutionY.get());
		sdl::windowSetFullscreen(graphicsWindowMode.get());
		renderScalePrivate = graphicsResolutionY.get() / BASE_DENOMINATOR;
	}

	// Sets up render scale. Resolution uses the height of a 4k screen as a base
	void CoreConfig::postInitialize() {
		renderScalePrivate = graphicsResolutionY.get() / BASE_DENOMINATOR;
	}
}