export module fbc.coreConfig;

import fbc.config;
import fbc.configItem;
import fbc.futil;
import fbc.gameLanguage;
import std;

export namespace fbc::core {
	export class CoreConfig : public cfg::Config {
	public:
		CoreConfig(str ID) : cfg::Config(ID) {}

		cfg::ConfigItem<int> gameActionSpeed = cfg::ConfigItem<int>(*this, "GameActionSpeed", 3);
		cfg::ConfigItem<bool> graphicsIsBorderless = cfg::ConfigItem<bool>(*this, "GraphicsIsBorderless", false);
		cfg::ConfigItem<bool> graphicsIsFullScreen = cfg::ConfigItem<bool>(*this, "GraphicsIsFullScreen", false);
		cfg::ConfigItem<bool> graphicsVSync = cfg::ConfigItem<bool>(*this, "GraphicsVSync", false);
		cfg::ConfigItem<int> graphicsFPS = cfg::ConfigItem<int>(*this, "GraphicsFPS", 60);
		cfg::ConfigItem<bool> graphicsParticleEffects = cfg::ConfigItem<bool>(*this, "GraphicsParticleEffects", true);
		cfg::ConfigItem<int> graphicsResolutionX = cfg::ConfigItem<int>(*this, "GraphicsResolutionX", 1920);
		cfg::ConfigItem<int> graphicsResolutionY = cfg::ConfigItem<int>(*this, "GraphicsResolutionY", 1080);
		cfg::ConfigItem<int> soundVolumeEffects = cfg::ConfigItem<int>(*this, "SoundVolumeEffects", 100);
		cfg::ConfigItem<int> soundVolumeMaster = cfg::ConfigItem<int>(*this, "SoundVolumeMaster", 100);
		cfg::ConfigItem<int> soundVolumeMusic = cfg::ConfigItem<int>(*this, "SoundVolumeMusic", 100);
		cfg::ConfigItem<str> textFont = cfg::ConfigItem<str>(*this, "TextFont", "");
		cfg::ConfigItem<bool> textIcons = cfg::ConfigItem<bool>(*this, "TextIcons", false);
		cfg::ConfigItem<loc::GameLanguage> textLanguage = cfg::ConfigItem<loc::GameLanguage>(*this, "TextIcons", loc::GameLanguage::ENG);
	};
}