export module fbc.ContentRegisterable;

import fbc.BaseContent;
import fbc.FUtil;
import sdl;
import std;

/*
 * Variant of KeyedItem that doesn't throw on duplicate values and that allows for deletion.
 */
namespace fbc {
	export template <typename C> struct ContentRegisterable {
		ContentRegisterable(BaseContent& source, strv id): source(source), id(id) {}
		virtual ~ContentRegisterable() = default;

		const str id;
		BaseContent& source;

		inline pair<str, str> toPair() const { return { source.id, id }; }

		inline static C* get(const pair<str,str>& idSearch) { return getOrDefault(idSearch.first, idSearch.second, nullptr); }
		inline static C* get(strv contentID, strv name) { return getOrDefault(contentID, name, nullptr); }

		static auto all();
		static C* getOrDefault(strv contentID, strv name, C* defaultValue);
		static C* registerCopy(C& copy);
		static C* registerData(uptr<C>&& copy);
		static vec<C*> allAsList();
		static void deleteData(strv contentID, strv name);
		template <typename Pred> static auto findAll(Pred predicate);
		template <typename Pred> static vec<C*> findAllAsList(Pred predicate);
	protected:
		inline static map<strv, map<strv, uptr<C>>>& registered() {
			static map<strv, map<strv, uptr<C>>> values;
			return values;
		}

		static map<strv, uptr<C>>* getInnerMap(strv contentID);
		static map<strv, uptr<C>>& tryRegisterInnerMap(BaseContent& content);
	};

	// Get every single instantiation of this class
	template<typename C> auto ContentRegisterable<C>::all()
	{
		return registered() | std::views::values | std::views::join | std::views::values | std::views::transform([](uptr<C>* item) {return item.get(); });
	}

	// Remove a registered item
	template<typename C> void ContentRegisterable<C>::deleteData(strv contentID, strv name)
	{
		registered().erase(name);
	}

	// Get a mapping corresponding to the content. Return null if none was found
	template<typename C> map<strv, uptr<C>>* ContentRegisterable<C>::getInnerMap(strv contentID)
	{
		auto& values = registered();
		auto it = values.find(contentID);
		if (it == values.end()) {
			return nullptr;
		}
		return &(it->second);
	}

	// Get a mapping corresponding to the content. Create the mapping if it didn't exist and link it to the source
	template<typename C> map<strv, uptr<C>>& ContentRegisterable<C>::tryRegisterInnerMap(BaseContent& content)
	{
		auto& values = registered();
		auto it = values.find(content.id);
		if (it == values.end()) {
			auto [mit, is] = values.emplace(content.id, map<strv, uptr<C>>());
			return mit->second;
		}
		return it->second;
	}

	// Get every single instantiation of this class as a list
	template<typename C> vec<C*> ContentRegisterable<C>::allAsList()
	{
		const auto& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			for (const auto& inner : pair.second) {
				result.emplace_back(inner.second.get());
			}
		}
		return result;
	}

	// Get a particular instantation of this class matching the given id, returning the defaultValue if not found
	template<typename C> C* ContentRegisterable<C>::getOrDefault(strv contentID, strv name, C* defaultValue)
	{
		map<strv, uptr<C>>* values = getInnerMap(contentID);
		if (values) {
			auto it = values->find(name);
			if (it == values->end()) {
				return defaultValue;
			}
			return it->second.get();
		}
		return defaultValue;
	}

	// Registers a copy of an existing object
	template<typename C> C* ContentRegisterable<C>::registerCopy(C& copy)
	{
		return registerData(make_unique<C>(copy));
	}

	// Registers a data object
	template<typename C> C* ContentRegisterable<C>::registerData(uptr<C>&& copy)
	{
		map<strv, uptr<C>>& values = tryRegisterInnerMap(copy->source);
		strv id = copy->id;
		auto [it, inserted] = values.try_emplace(id, move(copy));
		if (!inserted) {
			sdl::logInfo("ContentRegisterable with id already exists: " + str(id));
		}
		return it->second.get();
	}

	template<typename C> template<typename Pred> auto ContentRegisterable<C>::findAll(Pred predicate)
	{
		return all() | std::views::filter(predicate);
	}

	template<typename C> template<typename Pred> vec<C*> ContentRegisterable<C>::findAllAsList(Pred predicate)
	{
		const auto& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			for (const auto& inner : pair.second) {
				C* item = inner.second.get();
				if (predicate(item)) {
					result.emplace_back(item);
				}
			}
		}
		return result;
	}
}