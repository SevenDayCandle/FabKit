export module fbc.DynamicLoadables;

import fbc.BaseContent;
import fbc.Cache;
import fbc.ContentLoadables;
import fbc.FTexture;
import fbc.FUtil;
import fbc.ILoadable;
import std;

export namespace fbc {
	export template <c_ext<ILoadable> T> class DynamicLoadables : public ContentLoadables {
	public:
		DynamicLoadables(const BaseContent& content) : ContentLoadables(content) {}
		virtual ~DynamicLoadables() {}

		inline void dispose() override { items.clear(); }

		T* get(strv key);

		virtual void initialize() override;
	private:
		T* loadItem(strv key);
		umap<strv, uptr<T>> items;
	};

	// Attempt to fetch a cached texture. If none are found, generate one and put it into the map
	template <c_ext<ILoadable> T> T* DynamicLoadables<T>::get(strv key) {
		auto found = items.find(key);
		if (found != items.end()) {
			return found->second.get();
		}
		return loadItem(key);
	}

	// Reload all loaded items
	template <c_ext<ILoadable> T> void DynamicLoadables<T>::initialize()
	{
		for (uptr<T>& pair : items | std::views::values) {
			pair->reload();
		}
	}

	// Attempt to load a texture from disk, saving it into the map
	template <c_ext<ILoadable> T> T* DynamicLoadables<T>::loadItem(strv key)
	{
		path pathImpl = content.contentFolder;
		pathImpl /= ContentLoadables::getDirectoryPath<T>();
		pathImpl /= key;
		str pathStr = pathImpl.string();
		auto [it, inserted] = items.emplace(std::piecewise_construct,
			std::forward_as_tuple(key),
			std::forward_as_tuple(std::make_unique<T>(pathStr)));
		return it->second.get();
	}
}