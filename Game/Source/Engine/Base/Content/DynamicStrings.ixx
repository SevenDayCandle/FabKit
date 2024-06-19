export module fbc.DynamicStrings;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.FUtil;
import fbc.KeywordStrings;
import std;

export namespace fbc {
	export class DynamicStrings : public BaseStrings {
	public:
		DynamicStrings(const BaseContent& content): BaseStrings(content) {}
		virtual ~DynamicStrings() {}

		KeywordStrings* getKeywordStrings(strv path) override;
		void initialize() override;
	private:
		strumap<KeywordStrings> keywordStrings;
	};

	KeywordStrings* DynamicStrings::getKeywordStrings(strv path)
	{
		auto it = keywordStrings.find(path);
		if (it != keywordStrings.end()) {
			return &it->second;
		}
		return nullptr;
	}

	// Core contains UI strings, keyword strings
	void DynamicStrings::initialize()
	{
		loadKeywordStrings(keywordStrings);
	}
}