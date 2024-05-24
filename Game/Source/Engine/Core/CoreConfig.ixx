export module fbc.CoreConfig;

import fbc.Config;
import fbc.ConfigHotkey;
import fbc.ConfigItem;
import fbc.FUtil;
import fbc.Language;
import sdl;
import std;

export namespace fbc {
	constexpr float BASE_DENOMINATOR = 2160;
	const str FONT_BOLD = "Resources/Fonts/NotoSans-Bold.ttf";
	const str FONT_REGULAR = "Resources/Fonts/NotoSans-Regular.ttf";

	export class CoreConfig : public Config {
	public:
		CoreConfig(strv ID) : Config(ID) {}
		virtual ~CoreConfig() override {}

		ConfigItem<int> gameActionSpeed = ConfigItem<int>(*this, "GameActionSpeed", 3);
		ConfigItem<int> graphicsFPS = ConfigItem<int>(*this, "GraphicsFPS", 144);
		ConfigItem<bool> graphicsParticleEffects = ConfigItem<bool>(*this, "GraphicsParticleEffects", true);
		ConfigItem<int> graphicsResolutionX = ConfigItem<int>(*this, "GraphicsResolutionX", 1920);
		ConfigItem<int> graphicsResolutionY = ConfigItem<int>(*this, "GraphicsResolutionY", 1080);
		ConfigItem<bool> graphicsVSync = ConfigItem<bool>(*this, "GraphicsVSync", true);
		ConfigItem<int> graphicsWindowMode = ConfigItem<int>(*this, "GraphicsFPS", 0);
		ConfigItem<int> soundVolumeEffects = ConfigItem<int>(*this, "SoundVolumeEffects", 100);
		ConfigItem<int> soundVolumeMaster = ConfigItem<int>(*this, "SoundVolumeMaster", 100);
		ConfigItem<int> soundVolumeMusic = ConfigItem<int>(*this, "SoundVolumeMusic", 100);
		ConfigItem<str> textFont = ConfigItem<str>(*this, "TextFont", FONT_REGULAR);
		ConfigItem<str> textFontBold = ConfigItem<str>(*this, "TextFont", FONT_BOLD);
		ConfigItem<int> textFontScale = ConfigItem<int>(*this, "SoundVolumeMusic", 1);
		ConfigItem<bool> textIcons = ConfigItem<bool>(*this, "TextIcons", false);
		ConfigItem<str> textLanguage = ConfigItem<str>(*this, "TextIcons", lang::ENG);

		Hotkey actDirDown = Hotkey::add("ActDirDown", sdl::KEY_DOWN, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_DOWN);
		Hotkey actDirLeft = Hotkey::add("ActDirLeft", sdl::KEY_LEFT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_LEFT);
		Hotkey actDirRight = Hotkey::add("ActDirRight", sdl::KEY_RIGHT, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
		Hotkey actDirUp = Hotkey::add("ActDirUp", sdl::KEY_UP, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_UP);
		Hotkey actEsc = Hotkey::add("ActEsc", sdl::KEY_ESC, sdl::GamepadButton::SDL_GAMEPAD_BUTTON_INVALID);

		inline int getScreenXSize() { return graphicsResolutionX.get(); }
		inline int getScreenYSize() { return graphicsResolutionY.get(); };
		inline float fontScale() const noexcept { return fontScalePrivate; } // Gets the scale factor to resize fonts by. Resolution uses the height of a 4k screen as a base
		inline float fontScale(float mult) const noexcept { return fontScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.
		inline float renderScale() const noexcept { return renderScalePrivate; } // Gets the scale factor to resize elements by. Resolution uses the height of a 4k screen as a base
		inline float renderScale(float mult) const noexcept { return renderScalePrivate * mult; } // Multiplies the constant by the screen scale factor. ONLY USE THIS when you need to modify offsets within methods by some constant factor or by a size variable in a class, and NOT when initializing sizes on UI components.

		const Language& getLanguage();

		void postInitialize() override;
		void resizeWindow();
		void setupWindow();
	private:
		float fontScalePrivate = 1.0;
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

	void CoreConfig::postInitialize() {
		// Resolution uses the height of a 4k screen as a base
		renderScalePrivate = graphicsResolutionY.get() / BASE_DENOMINATOR;
		fontScalePrivate = renderScalePrivate * textFontScale.get();
	}

	// When the window size parameters change, we should resize the window and update renderScalePrivate
	void CoreConfig::resizeWindow()
	{
		sdl::windowSetSize(graphicsResolutionX.get(), graphicsResolutionY.get());
		postInitialize();
	}

	// Update the window from the config
	void CoreConfig::setupWindow() {
		sdl::initWindow(graphicsResolutionX.get(), graphicsResolutionY.get(), graphicsWindowMode.get(), graphicsVSync.get());
		graphicsResolutionX.addSubscriber([this](const int& val) {resizeWindow(); }); // TODO unify X and Y subscribers to avoid resizing window twice
		graphicsResolutionY.addSubscriber([this](const int& val) {resizeWindow(); });
		graphicsWindowMode.addSubscriber([this](const int& val) {sdl::windowSetFullscreen(val); });
		graphicsVSync.addSubscriber([this](const int& val) {sdl::updateVSync(val); });
	}
}