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

		inline str screen_setup_header() const { return uiStrings.at("screen_setup_header"); };
		inline str screen_title_header() const { return uiStrings.at("screen_title_header"); };
		inline str ui_cancel() const { return uiStrings.at("ui_cancel"); };
		inline str ui_close() const { return uiStrings.at("ui_close"); };
		inline str ui_confirm() const { return uiStrings.at("ui_confirm"); };
	private:
		umap<str, KeywordStrings> keywordStrings;
		umap<str, str> uiStrings;
	};

	// Core contains UI strings, keyword strings
	void CoreStrings::initialize()
	{
		loadUIStrings(uiStrings);
		loadKeywordStrings(keywordStrings);
	}
}