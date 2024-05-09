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

		// Get every single instantiation of this class
		static std::vector<std::reference_wrapper<C>> all() {
			const auto& values = registered();
			std::vector<std::reference_wrapper<C>> result;
			for (const auto& pair : values) {
				result.emplace_back(*static_cast<C*>(pair.second));
			}
			return result;
		}

		// Get a particular instantation of this class matching the given name
		static C& get(std::string_view name) {
			auto& values = registered();
			auto it = values.find(name);
			if (it == values.end()) {
				throw std::out_of_range("No KeyedItem with name: " + std::string(name));
			}
			return *static_cast<C*>(it->second);
		}
	protected:
		static std::map<std::string_view, KeyedItem*>& registered() {
			static std::map<std::string_view, KeyedItem*> values;
			return values;
		}
	};
}