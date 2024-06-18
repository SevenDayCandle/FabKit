module;

#include "glaze/glaze.hpp"

export module fbc.BaseStrings;

import fbc.BaseContent;
import fbc.ContentLoadables;
import fbc.CoreConfig;
import fbc.FUtil;
import fbc.KeywordStrings;
import fbc.Language;
import fbc.ObjectStrings;

export namespace fbc {
	constexpr strv DEFAULT_KEYWORDS = "KeywordStrings";
	constexpr strv DEFAULT_UI = "UIStrings";

	export class BaseStrings : public ContentLoadables {
	public:
		BaseStrings(const BaseContent& content) : ContentLoadables(content) {}
		virtual ~BaseStrings() {}

		virtual void dispose() {};
		virtual void initialize() {};
	protected:
		inline path getPathForLanguage(const strv& suffix) const {
			return getPathForLanguage(cfg.getLanguage(), suffix);
		};
		inline path getPathForLanguage(const Language& lang, const strv& suffix) const {
			path p = content.contentFolder;
			return (p / STRINGS_PATH / lang.name / suffix).replace_extension(futil::JSON_EXT);
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