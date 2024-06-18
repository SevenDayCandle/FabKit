export module fbc.CoreContent;

import fbc.BaseContent;
import fbc.CoreAudio;
import fbc.CoreConfig;
import fbc.CoreImages;
import fbc.CoreStrings;
import fbc.FFont;
import fbc.FUtil;
import sdl;
import std;

export namespace fbc {
	const str BASE_FOLDER = "/Resources";

	export class CoreContent : public fbc::BaseContent {
		static map<strv, BaseContent&> registeredContents;
	public:
		CoreContent(strv ID) : fbc::BaseContent(ID, sdl::dirBase() + BASE_FOLDER) {}

		CoreAudio audio = CoreAudio(*this);
		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		inline FFont& fontBold() { return *fontBoldData; }
		inline FFont& fontRegular() { return *fontRegularData; }
		inline FFont& fontSmall() { return *fontSmallData; }

		void dispose() override;
		void initialize() override;
		void initializeFonts();
		void postInitialize() override;
		void reloadFonts();
		void reloadImages() override;

		template <c_ext<BaseContent> T> static T registerContent(strv ID, strv contentFolder);
	private:
		uptr<FFont> fontBoldData;
		uptr<FFont> fontRegularData;
		uptr<FFont> fontSmallData;
	};

	export CoreContent cct = CoreContent(futil::FBC);

	// TODO
	void CoreContent::dispose()
	{
		images.dispose();
		fontBoldData = nullptr;
		fontRegularData = nullptr;
		fontSmallData = nullptr;
	}

	// TODO
	void CoreContent::initialize()
	{
		initializeFonts();
		audio.initialize();
		images.initialize();
		strings.initialize();
	}

	void CoreContent::initializeFonts()
	{
		fontBoldData = std::make_unique<FFont>(cfg.textFontBold.get(), 48, 2, 4);
		fontRegularData = std::make_unique<FFont>(cfg.textFont.get(), 48, 0, 4);
		fontSmallData = std::make_unique<FFont>(cfg.textFont.get(), 32, 0, 3);
	}

	// TODO
	void CoreContent::postInitialize()
	{
		audio.postInitialize();
		images.postInitialize();
		strings.postInitialize();
	}

	void CoreContent::reloadFonts()
	{
		fontBoldData->reloadFont();
		fontRegularData->reloadFont();
		fontSmallData->reloadFont();
	}

	void CoreContent::reloadImages()
	{
		images.initialize();
	}

	template<c_ext<BaseContent> T> T CoreContent::registerContent(strv ID, strv contentFolder)
	{
		T content = T(ID, contentFolder);
		registeredContents[content.ID] = content;
		return content;
	}
}