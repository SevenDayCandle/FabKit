export module fbc.IContentLoadables;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.ILoadable;
import fbc.FTexture;
import fbc.FMusic;
import fbc.FSound;
import sdl;
import std;

export namespace fbc {
	constexpr strv AUDIO_PATH = "Audio";
	constexpr strv IMAGE_PATH = "Images";

	export class IContentLoadables {
	public:
		IContentLoadables() {}
		virtual ~IContentLoadables() {}

		inline virtual void postInitialize() {}

		virtual void dispose() = 0;
		virtual void initialize() = 0;

		template <c_ext<ILoadable> T> static strv getDirectoryPath();
	};

	template<c_ext<ILoadable> T> strv IContentLoadables::getDirectoryPath()
	{
		if constexpr (std::is_base_of_v<FTexture, T>) {
			return IMAGE_PATH;
		}
		if constexpr (std::is_base_of_v<FSound, T> || std::is_base_of_v<FMusic, T>) {
			return AUDIO_PATH;
		}
		return IMAGE_PATH;
	}
}