export module fbc.ContentLoadables;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.ILoadable;
import fbc.FTexture;
import fbc.FMusic;
import fbc.FSound;
import std;

namespace fbc {
	export constexpr strv AUDIO_PATH = "Audio";
	export constexpr strv FONT_PATH = "Fonts";
	export constexpr strv IMAGE_PATH = "Images";
	export constexpr strv STRINGS_PATH = "Strings";

	export class ContentLoadables {
	public:
		ContentLoadables(const BaseContent& content) : content(content) {}
		virtual ~ContentLoadables() {}

		const BaseContent& content;

		virtual void dispose() = 0;
		virtual void initialize() = 0;

		template <c_ext<ILoadable> T> static strv getDirectoryPath();
	};

	template <c_ext<ILoadable> T> strv ContentLoadables::getDirectoryPath() {
		if constexpr (std::is_base_of_v<FTexture, T>) { return IMAGE_PATH; }
		if constexpr (std::is_base_of_v<FSound, T> || std::is_base_of_v<FMusic, T>) { return AUDIO_PATH; }
		return FONT_PATH;
	}
}
