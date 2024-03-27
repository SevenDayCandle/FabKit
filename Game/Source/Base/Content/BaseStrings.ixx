module;

#include "glaze/glaze.hpp"

export module fbc.baseStrings;

import fbc.baseContent;
import fbc.coreConfig;
import fbc.futil;
import fbc.gameLanguage;
import fbc.keywordStrings;
import fbc.objectStrings;

export namespace fbc {
	constexpr strv DEFAULT_KEYWORDS = "KeywordStrings";
	constexpr strv DEFAULT_UI = "UIStrings";
	constexpr strv LOCALIZATION_PATH = "Localization";

	export class BaseStrings {
	public:
		BaseStrings(BaseContent& content) : content(content) {}
		virtual ~BaseStrings() {}

		const BaseContent& content;

		virtual void initialize() {};
		virtual void postInitialize() {}
	protected:
		inline path getPathForLanguage(const strv& suffix) {
			return getPathForLanguage(cfg.textLanguage.get(), suffix);
		};
		inline path getPathForLanguage(const GameLanguage& lang, const strv& suffix) {
			path p = content.contentFolder;
			return (p / LOCALIZATION_PATH / langToStr(lang) / suffix).replace_extension(futil::JSON_EXT);
		};
		void loadKeywordStrings(unmap<str, KeywordStrings>& res, const strv& suffix);
		void loadObjectStrings(unmap<str, ObjectStrings>& res, const strv& suffix);
		void loadUIStrings(unmap<str, str>& res, const strv& suffix);
	};

	void BaseStrings::loadKeywordStrings(unmap<str, KeywordStrings>& res, const strv& suffix = DEFAULT_KEYWORDS)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	// TODO
	void BaseStrings::loadObjectStrings(unmap<str, ObjectStrings>& res, const strv& suffix)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	// TODO
	void BaseStrings::loadUIStrings(unmap<str, str>& res, const strv& suffix = DEFAULT_UI) {
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}
}