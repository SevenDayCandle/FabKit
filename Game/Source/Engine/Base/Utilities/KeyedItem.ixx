export module fbc.KeyedItem;

import std;

/*
 * A struct intended to mimic Java enums that can be expanded.
 * Every instance of a derivative class of KeyedItem must have a unique id
 */
namespace fbc {
	export template <typename C> struct KeyedItem {
	public:
		KeyedItem(const KeyedItem&) = delete;
		virtual ~KeyedItem() = default;

		const std::string_view id;

		bool operator<(const KeyedItem<C>& other) const { return this->id < other.id; }
		bool operator>(const KeyedItem<C>& other) const { return this->id > other.id; }
		bool operator==(const KeyedItem<C>& other) const { return this == &other; }
		std::filesystem::path operator/(const std::filesystem::path& other) const {return std::filesystem::path(id) / other;}
		friend std::ostream& operator<<(std::ostream& os, const KeyedItem& obj) { return os << obj.id; }
		operator std::string_view() const { return id; }

		inline static C* get(std::string_view name) { return getOrDefault(name, nullptr); }

		static auto all();
		static std::vector<C*> allAsList();
		static C& forceGet(std::string_view name);
		static C* getOrDefault(std::string_view name, C* defaultValue);
		template <typename Pred> static auto findAll(Pred predicate);
		template <typename Pred> static std::vector<C*> findAllAsList(Pred predicate);
	protected:
		KeyedItem(std::string_view name) : id(name) {
			std::map<std::string_view, C*>& values = registered();
			if (!values.emplace(this->id, static_cast<C*>(this)).second) {
				throw std::logic_error("Duplicate KeyedItem");
			}
		}
		static std::map<std::string_view, C*>& registered() {
			static std::map<std::string_view, C*> values;
			return values;
		}
	};

	// Get every single instantiation of this class
	template<typename C> auto KeyedItem<C>::all()
	{
		return registered() | std::views::values;
	}

	// Get every single instantiation of this class as a list
	template<typename C> std::vector<C*> KeyedItem<C>::allAsList()
	{
		const std::map<std::string_view, C*>& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			result.emplace_back(pair.second);
		}
		return result;
	}

	// Get a particular instantation of this class matching the given id
	template<typename C> C& KeyedItem<C>::forceGet(std::string_view name)
	{
		std::map<std::string_view, C*>& values = registered();
		auto it = values.find(name);
		if (it == values.end()) {
			throw std::out_of_range("No KeyedItem with id: " + std::string(name));
		}
		return *(it->second);
	}

	// Get a particular instantation of this class matching the given id. Returns the provided value if not found
	template<typename C> C* KeyedItem<C>::getOrDefault(std::string_view name, C* defaultValue)
	{
		std::map<std::string_view, C*>& values = registered();
		auto it = values.find(name);
		if (it == values.end()) {
			return defaultValue;
		}
		return it->second;
	}

	// Get every single instantiation of this class that passes the specified condition
	template<typename C> template<typename Pred> auto KeyedItem<C>::findAll(Pred predicate) {
		return all() | std::views::filter(predicate);
	}

	// Get every single instantiation of this class that passes the specified condition as a list
	template<typename C> template<typename Pred> std::vector<C*> KeyedItem<C>::findAllAsList(Pred predicate) {
		const std::map<std::string_view, C*>& values = registered();
		std::vector<C*> result;
		for (const auto& pair : values) {
			if (predicate(pair.second)) {
				result.emplace_back(pair.second);
			}
		}
		return result;
	}
}