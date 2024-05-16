export module fbc.BaseImages;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.Cache;
import fbc.FUtil;
import fbc.FTexture;
import fbc.RHorizontal;
import fbc.IDrawable;
import fbc.RVertical;
import std;

export namespace fbc {
	constexpr strv IMAGE_PATH = "Images";

	export class BaseImages {
	public:
		BaseImages(const BaseContent& content) : content(content) {}
		virtual ~BaseImages() {}

		const BaseContent& content;

		inline void dispose() { textures.clear(); }

		FTexture& get(const strv& key);

		virtual void initialize() {};
		virtual void postInitialize() {}
	protected:
		inline Cache<FTexture> cacheTexture(const strv& key) { return Cache<FTexture>([this, key]() { return loadTextureDirect(key); }); }
		inline Cache<RBordered> cacheBordered(Cache<FTexture> texture) { return Cache<RBordered>([this, texture]() { return new RBordered(texture.get()); }); }
		inline Cache<RHorizontal> cacheHorizontal(Cache<FTexture> texture) { return Cache<RHorizontal>([this, texture]() { return new RHorizontal(texture.get()); }); }
		inline Cache<RVertical> cacheVertical(Cache<FTexture> texture) { return Cache<RVertical>([this, texture]() { return new RVertical(texture.get()); }); }

		FTexture* loadTextureDirect(const strv& key);
	private:
		FTexture& loadTextureIntoMap(const strv& key);
		umap<strv, uptr<FTexture>> textures;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	FTexture& BaseImages::get(const strv& key) {
		auto found = textures.find(key);
		if (found != textures.end()) {
			return *found->second;
		}
		return loadTextureIntoMap(key);
	}

	// Attempt to load a texture from disk WITHOUT saving it into the map
	FTexture* BaseImages::loadTextureDirect(const strv& key)
	{
		path pathImpl = content.contentFolder;
		pathImpl /= IMAGE_PATH;
		pathImpl /= key;
		return new FTexture(pathImpl.string());
	}

	// Attempt to load a texture from disk, saving it into the map
	FTexture& BaseImages::loadTextureIntoMap(const strv& key)
	{
		path pathImpl = content.contentFolder;
		pathImpl /= IMAGE_PATH;
		pathImpl /= key;
		str pathStr = pathImpl.string();
		auto [it, inserted] = textures.emplace(std::piecewise_construct,
			std::forward_as_tuple(key),
			std::forward_as_tuple(std::make_unique<FTexture>(pathStr)));
		return *it->second;
	}
}