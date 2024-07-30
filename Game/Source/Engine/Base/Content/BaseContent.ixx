export module fbc.BaseContent;

import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import fbc.KeywordStrings;
import fbc.ObjectStrings;
import std;

namespace fbc {
	export constexpr strv CONTENT_ROOT = "/Content";

	export class BaseContent {
	public:
		BaseContent(strv id, strv contentFolder): id(id), contentFolder(contentFolder) {}
		virtual ~BaseContent() = default;

		const path contentFolder;
		const str id;

		inline virtual FMusic* getMusic(strv path) const { return nullptr; }
		inline virtual FSound* getSound(strv path) const { return nullptr; }
		inline virtual FTexture* getTexture(strv path) const { return nullptr; }
		inline virtual KeywordStrings* getKeywordStrings(strv path) const { return nullptr; }
		inline virtual ObjectStrings* getObjectStrings(strv type, strv path) const { return nullptr; }

		virtual void postInitialize() {}
		virtual void reloadAudio() {}
		virtual void reloadImages() {}

		virtual void dispose() = 0;
		virtual void initialize() = 0;

		static str sanitizeID(strv input);
	};

	/* Processes prospective IDs as follows
	 * 1. Replace all whitespace with underscores
	 * 2. Remove all punctuation
	 */
	str BaseContent::sanitizeID(strv input)
	{
		str res;
		res.reserve(input.size());

		std::ranges::for_each(input.begin(), input.end(),
			[&res](unsigned char c) {
				if (std::isspace(c)) {
					res.push_back('_');
				}
				else if (!std::ispunct(c)) {
					res.push_back(c);
				}
			});
		return res;
	}
}
