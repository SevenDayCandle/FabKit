export module fbc.KeyedItem;

import std;

/*
 * A struct intended to mimic Java enums that can be expanded.
 * Every instance of a derivative class of KeyedItem must have a unique name
 */
export namespace fbc {
	export template <typename C> struct KeyedItem {
		KeyedItem(std::string_view name): name(name) {
			auto& values = registered();
			if (!values.try_emplace(this->name, this).second) {
				throw std::logic_error("Duplicate KeyedItem with name: " + this->name);
			}
		}
		KeyedItem(const KeyedItem&) = delete;
		virtual ~KeyedItem() {}

		const std::string name;

		operator std::string() const { return name; }
		std::filesystem::path operator/(const std::filesystem::path& other) const {return std::filesystem::path(name) / other;}
		friend std::ostream& operator<<(std::ostream& os, const KeyedItem& obj) { return os << obj.name; }

		static std::vector<C*> all();
		static C& get(std::string_view name);
		static C* optGet(std::string_view name);

	protected:
		static std::map<std::string_view, KeyedItem*>& registered() {
			static std::map<std::string_view, KeyedItem*> values;
			return values;
		}
	};

	// Get every single instantiation of this class
	template<typename C> std::vector<C*> KeyedItem<C>::all()
	{
		const auto& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			result.emplace_back(static_cast<C*>(pair.second));
		}
		return result;
	}

	// Get a particular instantation of this class matching the given name
	template<typename C> C& KeyedItem<C>::get(std::string_view name)
	{
		auto& values = registered();
		auto it = values.find(name);
		if (it == values.end()) {
			throw std::out_of_range("No KeyedItem with name: " + std::string(name));
		}
		return *static_cast<C*>(it->second);
	}

	// Get a particular instantation of this class matching the given name. Does not throw on a missing key
	template<typename C> C* KeyedItem<C>::optGet(std::string_view name)
	{
		auto& values = registered();
		auto it = values.find(name);
		if (it == values.end()) {
			return nullptr;
		}
		return static_cast<C*>(it->second);
	}
}