export module fbc.CoreContent;

import fbc.BaseContent;
import fbc.CoreAudio;
import fbc.CoreConfig;
import fbc.CoreImages;
import fbc.CoreStrings;
import fbc.FFont;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import sdl;
import std;

namespace fbc {
	strv BASE_FOLDER = "/Resources";
	map<strv, BaseContent&> registeredContents;
}

export namespace fbc {

	export class CoreContent : public BaseContent {
	public:
		CoreContent(strv ID) : BaseContent(ID, sdl::dirBase() + str(BASE_FOLDER)) {}

		CoreAudio audio = CoreAudio(*this);
		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		inline FFont& fontBold() { return *fontBoldData; }
		inline FFont& fontRegular() { return *fontRegularData; }
		inline FFont& fontSmall() { return *fontSmallData; }

		FMusic* getMusic(strv content, strv path);
		FSound* getSound(strv content, strv path);
		FTexture* getTexture(strv content, strv path);
		void dispose() override;
		void initialize() override;
		void initializeFonts();
		void postInitialize() override;
		void reloadAudio() override;
		void reloadFonts();
		void reloadImages() override;

		template <c_ext<BaseContent> T> static T registerContent(strv ID, strv contentFolder);
	private:
		uptr<FFont> fontBoldData;
		uptr<FFont> fontRegularData;
		uptr<FFont> fontSmallData;
	};

	export CoreContent cct = CoreContent(futil::FBC);

	FMusic* CoreContent::getMusic(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second.getMusic(path);
		}
		return nullptr;
	}

	FSound* CoreContent::getSound(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second.getSound(path);
		}
		return nullptr;
	}

	FTexture* CoreContent::getTexture(strv content, strv path)
	{
		auto found = registeredContents.find(content);
		if (found != registeredContents.end()) {
			return found->second.getTexture(path);
		}
		return nullptr;
	}

	void CoreContent::dispose()
	{
		for (BaseContent& content : registeredContents | std::views::values) {
			content.dispose();
		}
		audio.dispose();
		images.dispose();
		strings.dispose();
		fontBoldData = nullptr;
		fontRegularData = nullptr;
		fontSmallData = nullptr;
	}

	void CoreContent::initialize()
	{
		initializeFonts();
		audio.initialize();
		images.initialize();
		strings.initialize();
		for (BaseContent& content : registeredContents | std::views::values) {
			content.initialize();
		}
	}

	void CoreContent::initializeFonts()
	{
		fontBoldData = std::make_unique<FFont>(cfg.textFontBold.get(), 48, 2, 4);
		fontRegularData = std::make_unique<FFont>(cfg.textFont.get(), 48, 0, 4);
		fontSmallData = std::make_unique<FFont>(cfg.textFont.get(), 32, 0, 3);
	}

	void CoreContent::postInitialize()
	{
		for (BaseContent& content : registeredContents | std::views::values) {
			content.postInitialize();
		}
	}

	void CoreContent::reloadFonts()
	{
		fontBoldData->reload();
		fontRegularData->reload();
		fontSmallData->reload();
	}

	void CoreContent::reloadAudio()
	{
		audio.initialize();
		for (BaseContent& content : registeredContents | std::views::values) {
			content.reloadAudio();
		}
	}

	void CoreContent::reloadImages()
	{
		images.initialize();
		for (BaseContent& content : registeredContents | std::views::values) {
			content.reloadImages();
		}
	}

	template<c_ext<BaseContent> T> T CoreContent::registerContent(strv ID, strv contentFolder)
	{
		T content = T(ID, contentFolder);
		registeredContents[content.ID] = content;
		return content;
	}
}