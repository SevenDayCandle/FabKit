export module fbc.DynamicStrings;

import fbc.BaseContent;
import fbc.BaseStrings;
import fbc.FUtil;
import fbc.KeywordStrings;
import fbc.ObjectStrings;
import std;

namespace fbc {
	export class DynamicStrings : public BaseStrings {
	public:
		DynamicStrings(const BaseContent& content): BaseStrings(content) {}

		KeywordStrings* getKeywordStrings(strv path) const override;
		ObjectStrings* getObjectStrings(strv type, strv path) const override;
		void initialize() override;
		void loadObjectStrings(const path& entry);
	private:
		mutable strumap<KeywordStrings> keywordStrings;
		mutable strumap<strumap<ObjectStrings>> objectStrings;
	};

	KeywordStrings* DynamicStrings::getKeywordStrings(strv path) const
	{
		auto it = keywordStrings.find(path);
		if (it != keywordStrings.end()) {
			return &it->second;
		}
		return nullptr;
	}

	ObjectStrings* DynamicStrings::getObjectStrings(strv type, strv path) const {
		auto mapit = objectStrings.find(type);
		if (mapit != objectStrings.end()) {
			strumap<ObjectStrings>& targMap = mapit->second;
			auto it = targMap.find(path);
			if (it != targMap.end()) {
				return &it->second;
			}
		}
		return nullptr;
	}

	// Core contains UI strings, keyword strings
	void DynamicStrings::initialize()
	{
		loadKeywordStrings(keywordStrings);

		// Dynamically load other object strings that have not been manually loaded earlier
		path folder = getBasePathForLanguage();
		if (std::filesystem::exists(folder)) {
			for (const dir_entry& entry : std::filesystem::directory_iterator(folder)) {
				if (entry.is_regular_file()) {
					loadObjectStrings(entry.path());
				}
			}
		}
	}

	void DynamicStrings::loadObjectStrings(const path& entry) {
		strumap<ObjectStrings> map;
		bool read = BaseStrings::loadObjectStringsFromFullPath(map, entry.string());
		if (read) {
			objectStrings.emplace(entry.stem().string(), move(map));
		}
	}
}