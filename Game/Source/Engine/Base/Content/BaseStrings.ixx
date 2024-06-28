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

namespace fbc {
	export constexpr strv DEFAULT_KEYWORDS = "KeywordStrings";
	export constexpr strv DEFAULT_UI = "UIStrings";

	export template <typename T> using strumap = umap<str, T, str_hash, equal_to<>>;

	export class BaseStrings : public ContentLoadables {
	public:
		BaseStrings(const BaseContent& content) : ContentLoadables(content) {}
		virtual ~BaseStrings() {}

		inline virtual KeywordStrings* getKeywordStrings(strv path) { return nullptr; }
		inline virtual ObjectStrings* getObjectStrings(strv type, strv path) { return nullptr; }

		virtual void dispose() {};
		virtual void initialize() {};
	protected:
		inline path getPathForLanguage(const strv& suffix) const {
			return getPathForLanguage(cfg.getLanguage(), suffix);
		};
		inline path getPathForLanguage(const Language& lang, const strv& suffix) const {
			path p = content.contentFolder;
			return (p / STRINGS_PATH / lang.id / suffix).replace_extension(futil::JSON_EXT);
		};
		void loadKeywordStrings(strumap<KeywordStrings>& res, const strv& suffix = DEFAULT_KEYWORDS);
		void loadObjectStrings(strumap<ObjectStrings>& res, const strv& suffix);
		void loadUIStrings(strumap<str>& res, const strv& suffix = DEFAULT_UI);
	};

	void BaseStrings::loadKeywordStrings(strumap<KeywordStrings>& res, const strv& suffix)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	void BaseStrings::loadObjectStrings(strumap<ObjectStrings>& res, const strv& suffix)
	{
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}

	void BaseStrings::loadUIStrings(strumap<str>& res, const strv& suffix) {
		glz::read_file_json(res, getPathForLanguage(suffix).string(), str{});
	}
}