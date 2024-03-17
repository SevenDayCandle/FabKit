export module fbc.coreContent;

import fbc.baseContent;
import fbc.coreImages;
import fbc.coreStrings;
import fbc.futil;
import raylib;
import std;

export namespace fbc {
	const str BASE_FOLDER = "/Resources";

	export class CoreContent : public fbc::BaseContent {
	public:
		CoreContent(strv ID) : fbc::BaseContent(ID, raylib::getWorkingDirectory() + BASE_FOLDER) {}

		CoreImages images = CoreImages(*this);
		CoreStrings strings = CoreStrings(*this);

		void dispose() override;
		void initialize() override;
		void postInitialize() override;
	};

	export CoreContent cct = CoreContent(futil::FBC);

	// TODO
	void CoreContent::dispose()
	{
	}

	// TODO
	void CoreContent::initialize()
	{
		images.initialize();
		strings.initialize();
	}

	// TODO
	void CoreContent::postInitialize()
	{
		images.postInitialize();
		strings.postInitialize();
	}
}