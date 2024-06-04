export module fbc.StaticImages;

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

	export class StaticImages {
	public:
		StaticImages(const BaseContent& content) : content(content) {}
		virtual ~StaticImages() {}

		const BaseContent& content;

		inline virtual void postInitialize() {}

		virtual void dispose();
		virtual void initialize();
	protected:
		inline FTexture& cacheTexture(const strv& key) { return static_cast<FTexture&>(*textures.emplace_back(std::make_unique<FTexture>(getTexturePath(key)))); }
		inline RBordered& cacheBordered(FTexture& texture) { return static_cast<RBordered&>(*textures.emplace_back(std::make_unique<RBordered>(texture))); }
		inline RHorizontal& cacheHorizontal(FTexture& texture) { return static_cast<RHorizontal&>(*textures.emplace_back(std::make_unique<RHorizontal>(texture))); }
		inline RVertical& cacheVertical(FTexture& texture) { return static_cast<RVertical&>(*textures.emplace_back(std::make_unique<RVertical>(texture))); }
	private:
		str getTexturePath(const strv& key) const;
		vec<uptr<ILoadable>> textures;
	};

	// Clear out all caches
	void StaticImages::dispose()
	{
		for (const uptr<ILoadable>& disposable : textures) {
			disposable->dispose();
		}
	}

	// Reload all caches
	void StaticImages::initialize()
	{
		for (const uptr<ILoadable>& disposable : textures) {
			disposable->reload();
		}
	}

	// Get the path for a texture
	str StaticImages::getTexturePath(const strv& key) const
	{
		path pathImpl = content.contentFolder;
		pathImpl /= IMAGE_PATH;
		pathImpl /= key;
		return pathImpl.string();
	}
}