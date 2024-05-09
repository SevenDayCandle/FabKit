export module fbc.CoreStrings;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.CoreConfig;
import fbc.FUtil;
import fbc.KeywordStrings;
import std;

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
		inline str ui_items() const { return uiStrings.at("ui_items"); };
		inline str ui_items(int val) const { return std::vformat(ui_items(), std::make_format_args(val)); };
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