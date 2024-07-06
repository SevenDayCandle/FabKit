export module fbc.ContentRegisterable;

import fbc.FUtil;
import sdl;
import std;

/*
 * Variant of KeyedItem that doesn't throw on duplicate values and that allows for deletion.
 */
namespace fbc {
	export template <typename C> struct ContentRegisterable {
		ContentRegisterable() {}
		virtual ~ContentRegisterable() = default;

		inline static C* get(strv name) { return getOrDefault(name, nullptr); }

		static auto all();
		static C* getAtPosition(int pos);
		static C* getOrDefault(strv name, C* defaultValue);
		static C* registerCopy(C& copy);
		static C* registerData(uptr<C>&& copy);
		static vec<C*> allAsList();
		static void deleteData(strv name);
		template <typename Pred> static auto findAll(Pred predicate);


		virtual operator strv() const = 0;
	protected:
		static map<strv, uptr<C>>& registered() {
			static map<strv, uptr<C>> values;
			return values;
		}
	};

	// Get every single instantiation of this class
	template<typename C> auto ContentRegisterable<C>::all()
	{
		return registered() | std::views::values | std::views::transform([](uptr<C>* item) {return item.get(); });
	}

	// Get an item at a particular position
	template<typename C> C* ContentRegisterable<C>::getAtPosition(int pos)
	{
		const auto& values = registered();
		if (pos < values.size()) {
			auto it = values.begin() + pos;
			return it->second.get();
		}
		return nullptr;
	}

	// Remove a registered item
	template<typename C> void ContentRegisterable<C>::deleteData(strv name)
	{
		registered().erase(name);
	}

	// Get every single instantiation of this class as a list
	template<typename C> vec<C*> ContentRegisterable<C>::allAsList()
	{
		const auto& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			result.emplace_back(pair.second.get());
		}
		return result;
	}

	// Get a particular instantation of this class matching the given id, returning the defaultValue if not found
	template<typename C> C* ContentRegisterable<C>::getOrDefault(strv name, C* defaultValue)
	{
		auto& values = registered();
		auto it = values.find(name);
		if (it == values.end()) {
			return defaultValue;
		}
		return it->second.get();
	}

	// Registers a copy of an existing object
	template<typename C> C* ContentRegisterable<C>::registerCopy(C& copy)
	{
		return registerData(make_unique<C>(copy));
	}

	// Registers a data object
	template<typename C> C* ContentRegisterable<C>::registerData(uptr<C>&& copy)
	{
		auto& values = registered();
		strv id = static_cast<strv>(*copy);
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
}