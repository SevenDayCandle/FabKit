export module fbc.coreConfig;

import fbc.config;
import fbc.configItem;
import fbc.ffont;
import fbc.futil;
import fbc.gameLanguage;
import sdl;
import std;

float renderScalePrivate = 1;
constexpr float BASE_DENOMINATOR = 2160;

export namespace fbc {
	export class CoreConfig : public Config {
	public:
		CoreConfig(strv ID) : Config(ID) {}
		virtual ~CoreConfig() {}

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
		ConfigItem<bool> textIcons = ConfigItem<bool>(*this, "TextIcons", false);
		ConfigItem<str> textLanguage = ConfigItem<str>(*this, "TextIcons", lang::ENG);

		void postInitialize() override;
	};

	export CoreConfig cfg = CoreConfig(futil::FBC);

	// Get the game language, defaulting to English if it is invalid
	export const GameLanguage& getLanguage() {
		try {
			return GameLanguage::get(cfg.textLanguage.get());
		}
		catch (exception e) {
			sdl::logError("Language failed to load: %s. Defaulting to ENG", e);
		}
		return lang::ENG;
	}

	// Get the supposed window width
	export int getScreenXSize() { return cfg.graphicsResolutionX.get(); }

	// Get the supposed window height
	export int getScreenYSize() { return cfg.graphicsResolutionY.get(); }

	// Update the window from the config
	export void refreshWindow() {
		sdl::windowSetSize(cfg.graphicsResolutionX.get(), cfg.graphicsResolutionY.get());
		sdl::windowSetFullscreen(cfg.graphicsWindowMode.get());
		renderScalePrivate = cfg.graphicsResolutionY.get() / BASE_DENOMINATOR;
	}

	// Return the current render scale for the window
	export float renderScale() {
		return renderScalePrivate;
	}

	// Return the size scaled by renderScale
	export float renderScale(float mult) {
		return renderScalePrivate * mult;
	} 


	// Sets up render scale. Resolution uses the height of a 4k screen as a base
	void CoreConfig::postInitialize() {
		renderScalePrivate = cfg.graphicsResolutionY.get() / BASE_DENOMINATOR;
	}
}