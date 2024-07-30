export module fbc.DynamicStrings;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.FUtil;
import fbc.KeywordStrings;
import std;

namespace fbc {
	export class DynamicStrings : public BaseStrings {
	public:
		DynamicStrings(const BaseContent& content): BaseStrings(content) {}

		KeywordStrings* getKeywordStrings(strv path) const override;
		void initialize() override;
	private:
		mutable strumap<KeywordStrings> keywordStrings;
	};

	KeywordStrings* DynamicStrings::getKeywordStrings(strv path) const
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