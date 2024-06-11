export module fbc.DynamicImages;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.Cache;
import fbc.FUtil;
import fbc.FTexture;
import fbc.ILoadable;
import fbc.RHorizontal;
import fbc.RVertical;
import std;

export namespace fbc {
	constexpr strv IMAGE_PATH = "Images";

	export class DynamicImages : public ILoadable {
	public:
		DynamicImages(const BaseContent& content) : content(content) {}
		virtual ~DynamicImages() {}

		const BaseContent& content;

		inline void dispose() { textures.clear(); }
		inline virtual void initialize() {};
		inline virtual void postInitialize() {}

		FTexture* get(const strv& key);

		virtual void reload() override;
	private:
		FTexture* loadTexture(const strv& key);
		umap<strv, uptr<FTexture>> textures;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	FTexture* DynamicImages::get(const strv& key) {
		auto found = textures.find(key);
		if (found != textures.end()) {
			return found->second.get();
		}
		return loadTexture(key);
	}

	// Reload all loaded textures
	void DynamicImages::reload()
	{
		for (auto& pair : textures) {
			pair.second->reload();
		}
	}

	// Attempt to load a texture from disk, saving it into the map
	FTexture* DynamicImages::loadTexture(const strv& key)
	{
		path pathImpl = content.contentFolder;
		pathImpl /= IMAGE_PATH;
		pathImpl /= key;
		str pathStr = pathImpl.string();
		auto [it, inserted] = textures.emplace(std::piecewise_construct,
			std::forward_as_tuple(key),
			std::forward_as_tuple(std::make_unique<FTexture>(pathStr)));
		return it->second.get();
	}
}