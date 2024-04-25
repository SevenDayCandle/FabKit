export module fbc.futil;

import fbc.keyedItem;
import sdl;
import std;

export namespace fbc {
	// std shorthands
	export template <typename T> using deque = std::deque<T>;
	export template <typename R> using func = std::function<R>;
	export template <typename T> using list = std::list<T>;
	export template <typename T> using opt = std::optional<T>;
	export template <typename T> using ref = std::reference_wrapper<T>;
	export template <typename T> using set = std::set<T>;
	export template <typename T> using span = std::span<T>;
	export template <typename T> using sptr = std::shared_ptr<T>;
	export template <typename T> using uptr = std::unique_ptr<T>;
	export template <typename T> using uset = std::unordered_set<T>;
	export template <typename T> using vec = std::vector<T>;
	export template <typename T, size_t U> using arr = std::array<T, U>;
	export template <typename T, typename U> using map = std::map<T, U>;
	export template <typename T, typename U> using pair = std::pair<T, U>;
	export template <typename T, typename U> using umap = std::unordered_map<T, U>;
	export using exception = std::exception;
	export using str = std::string;
	export using strv = std::string_view;
	export using uint32 = std::uint32_t;
	export using path = std::filesystem::path;

	// Const stuff, adapted from https://github.com/stephenberry/glaze
	// TODO just use the glz module version once it is available
	template <typename, template <typename...> typename> inline constexpr bool is_specialization_v = false;
	template <template <typename...> typename T, typename... Args> inline constexpr bool is_specialization_v<T<Args...>, T> = true;

	// Concepts
	export template<typename T> concept c_enum = std::is_enum_v<T>;
	export template<typename T, typename U> concept c_ext = std::is_base_of_v<T, U>;
	export template<typename Func, typename T, typename U> concept c_inv = requires(Func f, T t) {
		{ f(t) } -> std::convertible_to<U>;
	};
	export template<typename It, typename T> concept c_itr = std::ranges::range<It> && std::same_as<std::ranges::range_value_t<It>, T>;
	export template<typename T> concept c_keyed = std::is_base_of_v<keyed_item<T>, T>;
	export template<typename T> concept c_map = requires {
		typename T::key_type;
		typename T::mapped_type;
			requires std::is_default_constructible_v<T>;
	};
	export template<typename T> concept c_num = std::is_arithmetic_v<T>;
	export template<typename T> concept c_ref = is_specialization_v<T, std::reference_wrapper>;
	export template<typename It, typename T> concept c_set = c_itr<T, It>&& requires(It a, T v) {
		{ a.find(v) } -> std::convertible_to<typename It::iterator>;
	};
	export template<typename T> concept c_str = requires(T t) {
		std::string_view{ t };
	};
}

// Utility functions
export namespace fbc::futil {
	constexpr strv FBC = "fbc";
	constexpr strv JSON_EXT = ".json";
	constexpr strv MODS = "mods";
	constexpr strv VAL_FALSE = "false";
	constexpr strv VAL_TRUE = "true";

	// Wrapper function around std::all_of to check the entire container
	export template <typename T, typename Pred> bool all(const T& container, Pred predicate) {
		return std::all_of(container.begin(), container.end(), predicate);
	}

	// Wrapper function around std::any_of to check the entire container
	export template <typename T, typename Pred> bool any(const T& container, Pred predicate) {
		return std::any_of(container.begin(), container.end(), predicate);
	}

	// Create a lowercase version of a string-like
	export str toLowerCase(strv input) {
		str res;
		std::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return res;
	}

	// Modify an existing string to be lowercase
	export str& toLowerCaseInPlace(str& input) {
		std::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return input;
	}

	// Create an uppercase version of a string-like
	export str toUpperCase(strv input) {
		str res;
		std::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return res;
	}

	// Modify an existing string to be uppercase
	export str& toUpperCaseInPlace(str& input) {
		std::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return input;
	}

	// Find the first item in the container that matches the given value
	export template<typename T, c_itr<T> TCo> opt<T> find(const TCo& container, const T& value) {
		if constexpr (c_set<T, TCo>) {
			auto it = container.find(value);
			if (it != container.end()) {
				return *it;
			}
		}
		else {
			auto it = std::find(container.begin(), container.end(), value);
			if (it != container.end()) {
				return *it;
			}
		}
		return std::nullopt;
	}

	// Attempt to parse a string into an object
	// TODO handle iterables and maps
	export template <typename T> T fromString(strv input) {
		if constexpr (std::is_same_v<T, str>) {
			return str(input);
		}
		else if constexpr (std::is_same_v<T, bool> ) {
			str toLower = toLowerCase(input);
			if (toLower == VAL_TRUE || toLower == "1") {
				return true;
			}
			else if (toLower == VAL_FALSE || toLower == "0") {
				return false;
			}
			else {
				throw std::invalid_argument("Invalid string for conversion to bool: " + toLower);
			}
		}
		else if constexpr (std::is_same_v<T, int>) {
			return std::stoi(input.data());
		}
		else if constexpr (std::is_same_v<T, float>) {
			return std::stof(input.data());
		}
		else if constexpr (std::is_same_v<T, double>) {
			return std::stod(input.data());
		}
		else if constexpr (std::is_same_v<T, long>) {
			return std::stol(input.data());
		}
		else if constexpr (std::is_same_v<T, long long>) {
			return std::stoll(input.data());
		}
		else if constexpr (std::is_same_v<T, long double>) {
			return std::stold(input.data());
		}
		else if constexpr (std::is_same_v<T, unsigned long>) {
			return std::stoul(input.data());
		}
		else if constexpr (std::is_same_v<T, unsigned long long>) {
			return std::stoull(input.data());
		}
		else if constexpr (c_enum<T>) {
			int ind = std::stoi(input.data());
			return static_cast<T>(ind);
		}
		else if constexpr (c_keyed<T>) {
			return T::get(input);
		}
		else {
			static_assert(false, "Unsupported fromString type");
		}
		return T();
	}

	// Check whether the given container contains the given value
	export template<typename T, c_itr<T> TCo> bool has(const TCo& container, const T& value) {
		return find(container, value) != std::nullopt;
	}

	// Join a collection of strings with a delimiter
	export template<c_itr<strv> SCo> str joinStr(strv delimiter, SCo items) {
		str res;
		auto iter = items.begin();
		if (iter != items.end()) {
			res += *iter;
			++iter;
		}
		for (; iter != items.end(); ++iter) {
			res += delimiter + *iter;
		}
		return res;
	}

	// Represent a collection of objects as a joined string with a delimiter
	export template<typename TCo, typename Func> str joinStrMap(strv delimiter, const TCo& items, Func strFunc)
		requires std::ranges::range<TCo>&& c_inv<Func, std::ranges::range_value_t<TCo>, strv>
	{
		str res;
		auto iter = items.begin();
		if (iter != items.end()) {
			res += strFunc(*iter);
			++iter;
		}
		for (; iter != items.end(); ++iter) {
			res += delimiter;
			res += strFunc(*iter);
		}
		return res;
	}

	// Transform each of the values in the container into a new value and store the results in a list
	export template<typename T, typename U, c_itr<T> TCo, c_inv<T, U> Func> vec<U> map(const TCo& container, Func mapFunc) {
		vec<U> res(container.size());
		std::transform(container.begin(), container.end(), res.begin(), mapFunc);
		return res;
	}

	// Attempt to convert an arbitrary object into its string representation
	export template <typename T> str toString(const T& obj) {
		if constexpr (c_num<T>) {
			return std::to_string(obj);
		}
		if constexpr (std::is_same_v<T, str>) {
			return obj; 
		}
		if constexpr (std::is_same_v<T, bool>) {
			return obj ? VAL_TRUE : VAL_FALSE;
		}
		if constexpr (c_enum<T>) {
			return std::to_string(static_cast<std::underlying_type_t<T>>(obj));
		}
		if constexpr (c_str<T>) {
			return str(strv(obj));
		}
		if constexpr (c_map<T>) {
			std::string result = "{";
			auto iter = begin(obj);
			if (iter != end(obj)) {
				result += "\"" + toString(iter->first) + "\": " + toString(iter->second);
				++iter;
			}
			for (auto iter = map.begin(); iter != map.end(); ++iter) {
				result += ", \"" + toString(iter->first) + "\": " + toString(iter->second);
			}
			result += "}";
			return result;
		}
		if constexpr (c_ref<T>) {
			return toString(obj.get());
		}
		if constexpr (std::ranges::range<T>) {
			std::string result = "[";
			auto iter = obj.begin();
			if (iter != obj.end()) {
				result += toString(*iter);
				++iter;
			}
			for (; iter != obj.end(); ++iter) {
				result += ", " + toString(*iter);
			}
			result += "]";
			return result;
		}
		if constexpr (c_keyed<T>) {
			return obj;
		}
		std::ostringstream oss;
		oss << obj;
		return oss.str();
	}
}