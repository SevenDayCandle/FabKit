export module fbc.StaticLoadables;

import fbc.BaseContent;
import fbc.Cache;
import fbc.ContentLoadables;
import fbc.FMusic;
import fbc.FSound;
import fbc.FTexture;
import fbc.FUtil;
import fbc.ILoadable;
import fbc.RBordered;
import fbc.RHorizontal;
import fbc.RVertical;
import std;

namespace fbc {
	export class StaticLoadables : public ContentLoadables {
	public:
		StaticLoadables(const BaseContent& content) : ContentLoadables(content) {}

		virtual void dispose() override;
		virtual void initialize() override;
	protected:
		inline FMusic& cacheMusic(const strv& key) { return static_cast<FMusic&>(*items.emplace_back(std::make_unique<FMusic>(getPath(key, AUDIO_PATH)))); }
		inline FSound& cacheSound(const strv& key) { return static_cast<FSound&>(*items.emplace_back(std::make_unique<FSound>(getPath(key, AUDIO_PATH)))); }
		inline FTexture& cacheTexture(const strv& key) { return static_cast<FTexture&>(*items.emplace_back(std::make_unique<FTexture>(getPath(key, IMAGE_PATH)))); }
		inline RBordered& cacheBordered(const strv& key) { return static_cast<RBordered&>(*items.emplace_back(std::make_unique<RBordered>(getPath(key, IMAGE_PATH)))); }
		inline RHorizontal& cacheHorizontal(const strv& key) { return static_cast<RHorizontal&>(*items.emplace_back(std::make_unique<RHorizontal>(getPath(key, IMAGE_PATH)))); }
		inline RVertical& cacheVertical(const strv& key) { return static_cast<RVertical&>(*items.emplace_back(std::make_unique<RVertical>(getPath(key, IMAGE_PATH)))); }
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
		path pathImpl = content.contentFolder / folder / key;
		return pathImpl.string();
	}
}