export module fbc.StaticLoadables;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.Cache;
import fbc.FUtil;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.ILoadable;
import fbc.RHorizontal;
import fbc.RVertical;
import std;

export namespace fbc {
	constexpr strv AUDIO_PATH = "Audio";
	constexpr strv IMAGE_PATH = "Images";

	export class StaticLoadables {
	public:
		StaticLoadables(const BaseContent& content) : content(content) {}
		virtual ~StaticLoadables() {}

		const BaseContent& content;

		inline virtual void postInitialize() {}

		virtual void dispose();
		virtual void initialize();
	protected:
		inline FMusic& cacheMusic(const strv& key) { return static_cast<FMusic&>(*items.emplace_back(std::make_unique<FMusic>(getPath(key, AUDIO_PATH)))); }
		inline FSound& cacheSound(const strv& key) { return static_cast<FSound&>(*items.emplace_back(std::make_unique<FSound>(getPath(key, AUDIO_PATH)))); }
		inline FTexture& cacheTexture(const strv& key) { return static_cast<FTexture&>(*items.emplace_back(std::make_unique<FTexture>(getPath(key, IMAGE_PATH)))); }
		inline RBordered& cacheBordered(FTexture& texture) { return static_cast<RBordered&>(*items.emplace_back(std::make_unique<RBordered>(texture))); }
		inline RHorizontal& cacheHorizontal(FTexture& texture) { return static_cast<RHorizontal&>(*items.emplace_back(std::make_unique<RHorizontal>(texture))); }
		inline RVertical& cacheVertical(FTexture& texture) { return static_cast<RVertical&>(*items.emplace_back(std::make_unique<RVertical>(texture))); }
	private:
		str getPath(const strv& key, const strv& folder) const;
		vec<uptr<ILoadable>> items;
	};

	// Clear out all caches
	void StaticLoadables::dispose()
	{
		for (const uptr<ILoadable>& disposable : items) {
			disposable->dispose();
		}
	}

	// Reload all caches
	void StaticLoadables::initialize()
	{
		for (const uptr<ILoadable>& disposable : items) {
			disposable->reload();
		}
	}

	// Get the path for a texture
	str StaticLoadables::getPath(const strv& key, const strv& folder) const
	{
		path pathImpl = content.contentFolder;
		pathImpl /= folder;
		pathImpl /= key;
		return pathImpl.string();
	}
}