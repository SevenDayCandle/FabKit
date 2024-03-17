export module fbc.coreConfig;

import fbc.config;
import fbc.configItem;
import fbc.futil;
import fbc.gameLanguage;
import raylib;
import std;

float renderScalePrivate = 1;
constexpr float BASE_WIDTH = 1920;

export namespace fbc {
	export class CoreConfig : public Config {
	public:
		CoreConfig(strv ID) : Config(ID) {}

		ConfigItem<int> gameActionSpeed = ConfigItem<int>(*this, "GameActionSpeed", 3);
		ConfigItem<bool> graphicsIsBorderless = ConfigItem<bool>(*this, "GraphicsIsBorderless", false);
		ConfigItem<bool> graphicsIsFullScreen = ConfigItem<bool>(*this, "GraphicsIsFullScreen", false);
		ConfigItem<bool> graphicsVSync = ConfigItem<bool>(*this, "GraphicsVSync", false);
		ConfigItem<int> graphicsFPS = ConfigItem<int>(*this, "GraphicsFPS", 60);
		ConfigItem<bool> graphicsParticleEffects = ConfigItem<bool>(*this, "GraphicsParticleEffects", true);
		ConfigItem<int> graphicsResolutionX = ConfigItem<int>(*this, "GraphicsResolutionX", 1920);
		ConfigItem<int> graphicsResolutionY = ConfigItem<int>(*this, "GraphicsResolutionY", 1080);
		ConfigItem<int> soundVolumeEffects = ConfigItem<int>(*this, "SoundVolumeEffects", 100);
		ConfigItem<int> soundVolumeMaster = ConfigItem<int>(*this, "SoundVolumeMaster", 100);
		ConfigItem<int> soundVolumeMusic = ConfigItem<int>(*this, "SoundVolumeMusic", 100);
		ConfigItem<str> textFont = ConfigItem<str>(*this, "TextFont", "");
		ConfigItem<bool> textIcons = ConfigItem<bool>(*this, "TextIcons", false);
		ConfigItem<GameLanguage> textLanguage = ConfigItem<GameLanguage>(*this, "TextIcons", GameLanguage::ENG);
	};

	export CoreConfig cfg = CoreConfig(futil::FBC);

	// Get the supposed window width
	export int getScreenXSize() { return cfg.graphicsResolutionX.get(); }

	// Get the supposed window height
	export int getScreenYSize() { return cfg.graphicsResolutionY.get(); }

	// Update the window from the config
	export void refreshWindow() {
		raylib::setWindowSize(cfg.graphicsResolutionX.get(), cfg.graphicsResolutionY.get());
		if (raylib::isWindowFullscreen() != cfg.graphicsIsFullScreen.get()) {
			raylib::toggleFullscreen();
		}
		renderScalePrivate = cfg.graphicsResolutionX.get() / BASE_WIDTH;
	}

	// Update graphics settings from the config
	export void refreshGraphics() {
		raylib::setTargetFPS(cfg.graphicsFPS.get());
		refreshWindow();
	}

	// Return the current render scale for the window
	export float renderScale() {
		return renderScalePrivate;
	}

	// Return the size scaled by renderScale
	export float renderScale(float mult) {
		return renderScalePrivate * mult;
	}

	export void initializeCfg() {
		cfg.initialize();
		raylib::initWindow(getScreenXSize(), getScreenYSize(), "Fabricate");
	}
}