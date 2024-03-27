export module fbc.coreContent;

import fbc.baseContent;
import fbc.coreConfig;
import fbc.coreImages;
import fbc.coreStrings;
import fbc.ffont;
import fbc.futil;
import sdl;
import std;

export namespace fbc {
	const str BASE_FOLDER = "/Resources";

	export class CoreContent : public fbc::BaseContent {
	public:
		CoreContent(strv ID) : fbc::BaseContent(ID, sdl::dirBase() + BASE_FOLDER) {}

		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		inline FFont& fontBold() { return *fontBoldData; }
		inline FFont& fontRegular() { return *fontRegularData; }

		void dispose() override;
		void initialize() override;
		void initializeFonts();
		void postInitialize() override;
	private:
		uptr<FFont> fontBoldData;
		uptr<FFont> fontRegularData;
	};

	export CoreContent cct = CoreContent(futil::FBC);

	// TODO
	void CoreContent::dispose()
	{
	}

	// TODO
	void CoreContent::initialize()
	{
		initializeFonts();
		images.initialize();
		strings.initialize();
	}

	void CoreContent::initializeFonts()
	{
		fontRegularData = std::make_unique<FFont>(cfg.textFont.get());
	}

	// TODO
	void CoreContent::postInitialize()
	{
		images.postInitialize();
		strings.postInitialize();
	}
}