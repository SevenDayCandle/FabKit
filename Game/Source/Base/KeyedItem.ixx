export module fbc.keyedItem;

import std;

/*
 * A struct intended to mimic Java enums that can be expanded.
 * Every instance of a derivative class of keyed_item must have a unique name
 */
export namespace fbc {
	export template <typename C> struct keyed_item {
		keyed_item(std::string_view name): name(name) {
			auto& values = registered();
			if (!values.try_emplace(this->name, this).second) {
				throw std::logic_error("Duplicate keyed_item with name: " + this->name);
			}
		}
		keyed_item(const keyed_item&) = delete;
		virtual ~keyed_item() {}

		const std::string name;

		operator std::string() const { return name; }
		std::filesystem::path operator/(const std::filesystem::path& other) const {return std::filesystem::path(name) / other;}
		friend std::ostream& operator<<(std::ostream& os, const C& obj) { return os << obj; }

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
				throw std::out_of_range("No keyed_item with name: " + std::string(name));
			}
			return *static_cast<C*>(it->second);
		}
	protected:
		static std::map<std::string_view, keyed_item*>& registered() {
			static std::map<std::string_view, keyed_item*> values;
			return values;
		}
	};
}