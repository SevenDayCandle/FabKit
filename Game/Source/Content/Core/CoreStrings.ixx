export module fbc.coreStrings;

import fbc.baseContent;
import fbc.baseStrings;
import fbc.coreConfig;
import fbc.futil;
import fbc.keywordStrings;

export namespace fbc {
	export class CoreStrings : public BaseStrings {
	public:
		CoreStrings(BaseContent& cnt) : BaseStrings(cnt) {}

		void initialize() override;

		inline str screen_setup_header() { return uiStrings["screen_setup_header"]; };
		inline str screen_title_header() { return uiStrings["screen_title_header"]; };
		inline str ui_close() { return uiStrings["ui_close"]; };
	private:
		unmap<str, KeywordStrings> keywordStrings;
		unmap<str, str> uiStrings;
	};

	// Core contains UI strings, keyword strings
	void CoreStrings::initialize()
	{
		loadUIStrings(uiStrings);
		loadKeywordStrings(keywordStrings);
	}
}