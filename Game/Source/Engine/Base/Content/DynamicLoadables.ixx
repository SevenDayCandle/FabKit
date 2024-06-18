export module fbc.DynamicLoadables;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.Cache;
import fbc.FUtil;
import fbc.FTexture;
import fbc.ILoadable;
import fbc.IContentLoadables;
import fbc.RHorizontal;
import fbc.RVertical;
import std;

export namespace fbc {
	export template <c_ext<ILoadable> T> class DynamicLoadables : public IContentLoadables {
	public:
		DynamicLoadables(const BaseContent& content) : content(content) {}
		virtual ~DynamicLoadables() {}

		const BaseContent& content;

		inline void dispose() override { items.clear(); }

		T* get(const strv& key);

		virtual void initialize() override;
	private:
		T* loadItem(const strv& key);
		umap<strv, uptr<T>> items;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	template <c_ext<ILoadable> T> T* DynamicLoadables<T>::get(const strv& key) {
		auto found = items.find(key);
		if (found != items.end()) {
			return found->second.get();
		}
		return loadItem(key);
	}

	// Reload all loaded items
	template <c_ext<ILoadable> T> void DynamicLoadables<T>::initialize()
	{
		for (auto& pair : items) {
			pair.second->reload();
		}
	}

	// Attempt to load a texture from disk, saving it into the map
	template <c_ext<ILoadable> T> T* DynamicLoadables<T>::loadItem(const strv& key)
	{
		path pathImpl = content.contentFolder;
		pathImpl /= IContentLoadables::getDirectoryPath<T>();
		pathImpl /= key;
		str pathStr = pathImpl.string();
		auto [it, inserted] = items.emplace(std::piecewise_construct,
			std::forward_as_tuple(key),
			std::forward_as_tuple(std::make_unique<T>(pathStr)));
		return it->second.get();
	}
}