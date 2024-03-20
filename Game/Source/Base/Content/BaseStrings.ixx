module;

#include "glaze/glaze.hpp"

export module fbc.baseStrings;

import fbc.baseContent;
import fbc.coreConfig;
import fbc.futil;
import fbc.gameLanguage;
import fbc.keywordStrings;
import fbc.objectStrings;
import raylib;

export namespace fbc {
	const str DEFAULT_KEYWORDS = "keyword";
	const str LOCALIZATION_PATH = "Localization";

	export class BaseStrings {
	public:
		BaseStrings(BaseContent& content) : content(content) {}
		virtual ~BaseStrings() {}

		const BaseContent& content;

		inline unmap<str, KeywordStrings> loadKeywordStrings() { return loadKeywordStrings(DEFAULT_KEYWORDS); }
		unmap<str, KeywordStrings> loadKeywordStrings(const strv& suffix);
		unmap<str, ObjectStrings> loadObjectStrings(const strv& suffix);
		unmap<str, str> loadUIStrings(const strv& suffix);
		virtual void initialize() {};
		virtual void postInitialize() {}
	protected:
		inline path getPathForLanguage(const strv& suffix) {
			return getPathForLanguage(cfg.textLanguage.get(), suffix);
		};
		inline path getPathForLanguage(const GameLanguage& lang, const strv& suffix) {
			path p = content.contentFolder;
			return p / LOCALIZATION_PATH / langToStr(lang) / suffix / futil::JSON_EXT;
		};
	};

	// TODO
	unmap<str, KeywordStrings> BaseStrings::loadKeywordStrings(const strv& suffix)
	{
		return unmap<str, KeywordStrings>();
	}

	// TODO
	unmap<str, ObjectStrings> BaseStrings::loadObjectStrings(const strv& suffix)
	{
		return unmap<str, ObjectStrings>();
	}

	// TODO
	unmap<str, str> BaseStrings::loadUIStrings(const strv& suffix) {
		return unmap<str, str>();
	}
}