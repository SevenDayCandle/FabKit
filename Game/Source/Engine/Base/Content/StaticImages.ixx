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
		inline Cache<FTexture>& cacheTexture(const strv& key) { return static_cast<Cache<FTexture>&>(*textures.emplace_back(std::make_unique<Cache<FTexture>>([this, key]() {return new FTexture(getTexturePath(key)); }))); }
		inline Cache<RBordered>& cacheBordered(const Cache<FTexture>& texture) { return static_cast<Cache<RBordered>&>(*textures.emplace_back(std::make_unique<Cache<RBordered>>([this, texture]() { return new RBordered(texture.get()); }))); }
		inline Cache<RHorizontal>& cacheHorizontal(const Cache<FTexture>& texture) { return static_cast<Cache<RHorizontal>&>(*textures.emplace_back(std::make_unique<Cache<RHorizontal>>([this, texture]() { return new RHorizontal(texture.get()); }))); }
		inline Cache<RVertical>& cacheVertical(const Cache<FTexture>& texture) { return static_cast<Cache<RVertical>&>(*textures.emplace_back(std::make_unique<Cache<RVertical>>([this, texture]() { return new RVertical(texture.get()); }))); }
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