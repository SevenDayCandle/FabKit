module;

#include "glaze/glaze.hpp"

export module fbc.baseStrings;

import fbc.baseContent;
import fbc.coreConfig;
import fbc.futil;
import fbc.language;
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
			return getPathForLanguage(cfg.getLanguage(), suffix);
		};
		inline path getPathForLanguage(const Language& lang, const strv& suffix) {
			path p = content.contentFolder;
			return (p / LOCALIZATION_PATH / lang.name / suffix).replace_extension(futil::JSON_EXT);
		};
		void loadKeywordStrings(umap<str, KeywordStrings>& res, const strv& suffix = DEFAULT_KEYWORDS);
		void loadObjectStrings(umap<str, ObjectStrings>& res, const strv& suffix);
		void loadUIStrings(umap<str, str>& res, const strv& suffix = DEFAULT_UI);
	};

	void BaseStrings::loadKeywordStrings(umap<str, KeywordStrings>& res, const strv& suffix)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	void BaseStrings::loadObjectStrings(umap<str, ObjectStrings>& res, const strv& suffix)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	void BaseStrings::loadUIStrings(umap<str, str>& res, const strv& suffix) {
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}
}