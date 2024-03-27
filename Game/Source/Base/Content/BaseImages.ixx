export module fbc.baseImages;

import fbc.baseContent;
import fbc.futil;
import fbc.ftexture;

export namespace fbc {
	constexpr strv IMAGE_PATH = "Images";

	export class BaseImages {
	public:
		BaseImages(const BaseContent& content) : content(content) {}
		virtual ~BaseImages() {}

		const BaseContent& content;

		FTexture& getTexture(const strv& path);
		virtual void initialize() {};
		virtual void postInitialize() {}
	private:
		FTexture& loadTexture(const strv& path);
		unmap<strv, uptr<FTexture>> textures;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	FTexture& BaseImages::getTexture(const strv& key) {
		auto found = textures.find(key);
		if (found != textures.end()) {
			return *found->second;
		}
		return loadTexture(key);
	}

	// Attempt to load a texture from disk
	FTexture& BaseImages::loadTexture(const strv& key)
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