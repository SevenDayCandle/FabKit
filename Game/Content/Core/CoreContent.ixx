export module fbc.coreContent;

import fbc.baseContent;
import fbc.coreConfig;
import fbc.futil;

export namespace fbc::core {
	export class CoreContent : public fbc::content::BaseContent {
	public:
		CoreContent(const str& ID) : fbc::content::BaseContent(ID) {}

		CoreConfig cfg = CoreConfig(ID);
		void dispose();
		void initialize();
		void postInitialize();
	protected:
		path getContentFolder();
	};

	// TODO
	void CoreContent::dispose()
	{
	}

	// TODO
	void CoreContent::initialize()
	{
		cfg.initialize();
	}

	// TODO
	void CoreContent::postInitialize()
	{
	}

	// TODO
	path CoreContent::getContentFolder()
	{
		return path();
	}

}