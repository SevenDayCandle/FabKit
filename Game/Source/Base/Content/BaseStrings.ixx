module;

#include "glaze/glaze.hpp"

export module fbc.baseStrings;

import fbc;
import fbc.baseContent;
import fbc.futil;
import fbc.gameLanguage;
import fbc.keywordStrings;
import fbc.objectStrings;
import raylib;

export namespace fbc::content {
	const str DEFAULT_KEYWORDS = "keyword";
	const str LOCALIZATION_PATH = "Localization";

	export class BaseStrings {
	public:
		BaseStrings(const sptr<BaseContent> content) : content(content) {}
		virtual ~BaseStrings() {}

		const sptr<BaseContent> content;

		inline unmap<str, loc::KeywordStrings> loadKeywordStrings() { return loadKeywordStrings(DEFAULT_KEYWORDS); }
		unmap<str, loc::KeywordStrings> loadKeywordStrings(const str& suffix);
		unmap<str, loc::ObjectStrings> loadObjectStrings(const str& suffix);
		virtual void postInitialize() {}

		virtual void dispose() = 0;
		virtual void initialize() = 0;
	protected:
		virtual path getStringsFolder() = 0;
		inline path getPathForLanguage(const str& suffix) {
			return getPathForLanguage(fbc::cct.cfg.textLanguage.get(), suffix);
		};
		inline path getPathForLanguage(const loc::GameLanguage& lang, const str& suffix) {
			return getStringsFolder() / loc::langToStr(lang) / suffix / fbc::JSON_EXT;
		};
	};

	// TODO
	unmap<str, loc::KeywordStrings> BaseStrings::loadKeywordStrings(const str& suffix)
	{
		return unmap<str, loc::KeywordStrings>();
	}

	// TODO
	unmap<str, loc::ObjectStrings> BaseStrings::loadObjectStrings(const str& suffix)
	{
		return unmap<str, loc::ObjectStrings>();
	}
}