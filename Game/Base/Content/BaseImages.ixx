export module fbc.baseImages;

import fbc.futil;
import fbc.ftexture;

export namespace fbc::content {

	export class BaseImages {
	public:
		BaseImages(const str& ID) : ID(ID) {}
		virtual ~BaseImages() {}

		const str ID;

		sptr<FTexture> getTexture(const str& path);
		virtual void dispose() = 0;
		virtual void initialize() = 0;
		virtual void postInitialize() = 0;
	protected:
		virtual path getContentFolder() = 0;
	private:
		sptr<FTexture> loadTexture(const str& path);
		unmap<str, sptr<FTexture>> textures;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	sptr<FTexture> BaseImages::getTexture(const str& path) {
		auto found = textures.find(path);
		if (found != textures.end()) {
			return found->second;
		}
		sptr<FTexture> tex = loadTexture(path);
		textures[path] = tex;
		return tex;
	}

	// Attempt to load a texture from disk
	sptr<FTexture> BaseImages::loadTexture(const str& pathStr)
	{
		path pathImpl = getContentFolder() / pathStr;
		return FTexture::loadTexture(pathImpl.string());
	}
}