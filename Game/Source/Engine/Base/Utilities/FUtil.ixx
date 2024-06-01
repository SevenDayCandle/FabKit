export module fbc.FUtil;

import fbc.KeyedItem;
import fbc.Iserializable;
import sdl;
import std;

export namespace fbc {
	// std shorthands. Sorry peeps
	export template <typename T> using dec_t = std::decay_t<T>;
	export template <typename T> using deque = std::deque<T>;
	export template <typename R> using func = std::function<R>;
	export template <typename T> using ilist = std::initializer_list<T>;
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
	export using any = std::any;
	export using exception = std::exception;
	export using int32 = std::int32_t;
	export using str = std::string;
	export using strv = std::string_view;
	export using uint32 = std::uint32_t;
	export using path = std::filesystem::path;

	// Const stuff, adapted from https://github.com/stephenberry/glaze
	// TODO just use the glz module version once it is available
	export template <typename, template <typename...> typename> inline constexpr bool is_specialization_v = false;
	export template <template <typename...> typename T, typename... Args> inline constexpr bool is_specialization_v<T<Args...>, T> = true;

	// Concepts
	export template<typename T> concept c_enum = std::is_enum_v<T>;
	export template<typename T, typename U> concept c_ext = std::is_base_of_v<U, T>;
	export template<typename Func, typename T, typename U> concept c_invc = requires(Func f, T t) {
		{ f(t) } -> std::convertible_to<U>;
	};
	export template<typename It, typename T> concept c_itr = std::ranges::range<It> && std::same_as<std::ranges::range_value_t<It>, T>;
	export template<typename T> concept c_keyed = std::is_base_of_v<KeyedItem<T>, T>;
	export template<typename T> concept c_map = requires {
		typename T::key_type;
		typename T::mapped_type;
			requires std::is_default_constructible_v<T>;
	};
	export template<typename TCo, typename T, typename U> concept c_map_of = std::ranges::range<TCo> &&
		requires {
		typename TCo::key_type;
		typename TCo::mapped_type;
			requires std::same_as<typename TCo::key_type, T>;
			requires std::same_as<typename TCo::mapped_type, U>;
	};
	export template<typename T> concept c_num = std::is_arithmetic_v<T>;
	export template<typename T> concept c_pair = is_specialization_v<T, std::pair>;
	export template<typename T> concept c_push = requires(T t, typename T::value_type v) {
		{ t.push_back(v) } -> std::same_as<void>;
	};
	export template<typename T> concept c_ref = is_specialization_v<T, std::reference_wrapper>;
	export template<typename It, typename T> concept c_set = c_itr<T, It>&& requires(It a, T v) {
		{ a.find(v) } -> std::convertible_to<typename It::iterator>;
	};
	export template<typename T> concept c_serial = std::is_base_of_v<ISerializable, T>;
	export template<typename T> concept c_str = requires(T t) {
		std::string_view{ t };
	};
	export template<typename T, typename... Args> concept c_varg = (std::same_as<T, Args> && ...);;
	export template<typename T> concept c_vec = is_specialization_v<T, std::vector>;
}

// Utility functions
export namespace fbc::futil {
	export constexpr strv FBC = "fbc";
	export constexpr strv JSON_EXT = ".json";
	export constexpr strv MODS = "mods";
	export constexpr strv VAL_FALSE = "false";
	export constexpr strv VAL_TRUE = "true";

	export bool isNumeric(strv text);
	export bool isPrefix(strv source, strv prefix);
	export str dimensionString(const pair<int, int>& p);
	export str dimensionString(int x, int y);
	export str toLowerCase(strv input);
	export str toUpperCase(strv input);
	export str unescape(strv input, size_t& pos);
	export str& toLowerCaseInPlace(str& input);
	export str& toUpperCaseInPlace(str& input);
	export strv getView(strv input, size_t& pos);
	export template <c_itr<strv> SCo> str joinStr(strv delimiter, SCo items);
	export template <typename T, c_itr<T> TCo> bool has(const TCo& container, const T& value);
	export template <typename T, c_itr<T> TCo> opt<T> find(const TCo& container, const T& value);
	export template <typename T, typename Pred> bool all(const T& container, Pred predicate);
	export template <typename T, typename Pred> bool any(const T& container, Pred predicate);
	export template <typename T, typename U, c_itr<T> TCo, c_invc<T, U> Func> vec<U> transform(const TCo& container, Func mapFunc);
	export template <typename T, typename U, typename V, c_map_of<T, U> TCo, c_invc<U, V> Func> map<T, V> transformMap(const TCo& src, Func mapFunc);
	export template <typename T, typename U, typename V, c_map_of<T, U> TCo, c_invc<U, V> Func> umap<T, V> transformUmap(const TCo& src, Func mapFunc);
	export template <typename T> str toString(const T& obj);
	export template <typename T> str toStringWrapped(const T& obj);
	export template <typename T> T fromString(strv input);
	export template <typename T> T fromString(strv input, size_t& pos);
	export template <typename TCo, typename Func> str joinStrMap(strv delimiter, const TCo& items, Func strFunc) requires std::ranges::range<TCo>&& c_invc<Func, std::ranges::range_value_t<TCo>, strv>;
	
	/*
	DEFINITIONS
	*/


	// Wrapper function around std::all_of to check the entire container
	export template <typename T, typename Pred> bool all(const T& container, Pred predicate) {
		return std::all_of(container.begin(), container.end(), predicate);
	}

	// Wrapper function around std::any_of to check the entire container
	export template <typename T, typename Pred> bool any(const T& container, Pred predicate) {
		return std::any_of(container.begin(), container.end(), predicate);
	}

	// Format a pair as a dimension
	export str dimensionString(int x, int y) {
		return std::to_string(x) + "x" + std::to_string(x);
	}

	export str dimensionString(const pair<int,int>& p) {
		return dimensionString(p.first, p.second);
	}

	// Checks if a string-like starts with another string-like
	export bool isPrefix(strv source, strv prefix) {
		if (prefix.size() > source.size()) {
			return false;
		}
		for (int i = 0; i < prefix.size(); ++i) {
			if (std::tolower(source[i]) != std::tolower(prefix[i])) {
				return false;
			}
		}
		return true;
	}

	// Create a lowercase version of a string-like
	export str toLowerCase(strv input) {
		str res;
		std::ranges::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return res;
	}

	// Modify an existing string to be lowercase
	export str& toLowerCaseInPlace(str& input) {
		std::ranges::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return input;
	}

	// Create an uppercase version of a string-like
	export str toUpperCase(strv input) {
		str res;
		std::ranges::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return res;
	}

	// Modify an existing string to be uppercase
	export str& toUpperCaseInPlace(str& input) {
		std::ranges::transform(input.begin(), input.end(), input.begin(),
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

	// Check whether the given container contains the given value
	export template<typename T, c_itr<T> TCo> bool has(const TCo& container, const T& value) {
		return find(container, value) != std::nullopt;
	}

	// Check whether the text can be converted into a number
	export bool isNumeric(strv text) {
		return !text.empty() && std::all_of(text.begin(), text.end(), [](const char c) {return std::isdigit(c); });
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
		requires std::ranges::range<TCo>&& c_invc<Func, std::ranges::range_value_t<TCo>, strv>
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

	// Attempt to convert an arbitrary object into a regular string representation
	export template <typename T> str toString(const T& obj) {
		if constexpr (c_num<T>) {
			return std::to_string(obj);
		}
		else if constexpr (std::is_same_v<T, str>) {
			return obj; // When saved to a JSON, this gets automatically wrapped with quotes
		}
		else if constexpr (std::is_same_v<T, bool>) {
			return obj ? str(VAL_TRUE) : str(VAL_FALSE);
		}
		else if constexpr (c_enum<T>) {
			return std::to_string(static_cast<std::underlying_type_t<T>>(obj));
		}
		else if constexpr (c_str<T>) {
			return str(strv(obj));
		}
		else if constexpr (c_pair<T>) {
			return "[" + toStringWrapped(obj.first) + ", " + toStringWrapped(obj.second) + "]";
		}
		else if constexpr (c_map<T>) {
			std::string result = "{";
			auto iter = begin(obj);
			if (iter != end(obj)) {
				result += toStringWrapped(iter->first) + ": " + toStringWrapped(iter->second);
				++iter;
			}
			for (; iter != end(obj); ++iter) {
				result += ", " + toStringWrapped(iter->first) + ": " + toStringWrapped(iter->second);
			}
			result += "}";
			return result;
		}
		else if constexpr (c_ref<T>) {
			return toString(obj.get());
		}
		else if constexpr (std::ranges::range<T>) {
			std::string result = "[";
			auto iter = obj.begin();
			if (iter != obj.end()) {
				result += toStringWrapped(*iter);
				++iter;
			}
			for (; iter != obj.end(); ++iter) {
				result += ", " + toStringWrapped(*iter);
			}
			result += "]";
			return result;
		}
		else if constexpr (c_keyed<T>) {
			return obj;
		}
		else {
			std::ostringstream oss;
			oss << obj;
			return oss.str();
		}
	}

	// Same as toString but applies string quotes on strings (used for JSON serialization)
	export template <typename T> str toStringWrapped(const T& obj) {
		if constexpr (std::is_same_v<T, str>) {
			return '"' + obj + '"';
		}
		if constexpr (c_str<T>) {
			return '"' + obj + '"';
		}
		if constexpr (c_ref<T>) {
			return toStringWrapped(obj.get());
		}
		return toString(obj);
	}

	// Transform each of the values in the container into a new value and store the results in a list
	export template<typename T, typename U, c_itr<T> TCo, c_invc<T, U> Func> vec<U> transform(const TCo& container, Func mapFunc) {
		vec<U> res(container.size());
		std::transform(container.begin(), container.end(), res.begin(), mapFunc);
		return res;
	}

	// Transform each of the values in the map into a new map
	export template<typename T, typename U, typename V, c_map_of<T,U> TCo, c_invc<U, V> Func> map<T, V> transformMap(const TCo& src, Func mapFunc) {
		map<T, V> res;
		for (const auto& p : src) {
			res[p.first] = mapFunc(p.second);
		}
		return res;
	}

	// Transform each of the values in the map into a new unordered map
	export template<typename T, typename U, typename V, c_map_of<T, U> TCo, c_invc<U, V> Func> umap<T, V> transformUmap(const TCo& src, Func mapFunc) {
		umap<T, V> res;
		for (const auto& p : src) {
			res[p.first] = mapFunc(p.second);
		}
		return res;
	}

	// For types that do not use syntax characters, we can safely treat everything in between this pos and the next syntax character as being part of the object to be deserialized
	export strv getView(strv input, size_t& pos)
	{
		size_t start = pos;
		while (pos < input.size()) {
			switch (input[pos]) {
			case ',':
			case ' ':
			case ';':
			case '}':
				return strv(input.data() + start, pos - start);
			default:
				++pos;
			}
		}
		return strv(input.data() + start, pos - start);
	}

	// Removes quotes and escapes from a JSON-string object
	export str unescape(strv input, size_t& pos) {
		// No need to unescape string-likes that are not quoted
		if (input[pos] != '"') {
			return str(input);
		}
		++pos;

		str value;
		bool escape = false;

		while (pos < input.size()) {
			char c = input[pos++];
			if (escape) {
				value += c;
				escape = false;
			}
			else {
				switch (c) {
				case '\\':
					escape = true;
					break;
				case '"':
					return value; // End of the string view section
				default:
					value += c;
				}
			}
		}
		return value;
	}

	// Attempt to parse a JSON-like string into an object
	// TODO handle iterables and maps
	export template <typename T> T fromString(strv input) {
		size_t pos = 0;
		return fromString<T>(input, pos);
	}

	export template <typename T> T fromString(strv input, size_t& pos) {
		// These use syntax characters and handle iteration by their own logic
		if constexpr (std::is_same_v<T, str>) {
			return unescape(input, pos);
		}
		else if constexpr (c_push<T>) {
			T res;

			// Lists start with bracket. Note that subsequent brackets should start parsing 
			if (input[pos] == '[') {
				++pos;
			}

			while (pos < input.size()) {
				switch (input[pos]) {
				case ' ':
				case ',':
					++pos;
					break;
				case ']':
					++pos;
					return res; // End of array
				default:
					res.push_back(fromString<auto>(input, pos));
					break;
				}
			}

			return res;
		}
		else if constexpr (c_pair<T>) {
			pair<typename T::first_type, typename T::second_type> p;

			// Lists start with bracket. Note that subsequent brackets should start parsing 
			if (input[pos] == '[') {
				++pos;
			}

			p.first = fromString<typename T::first_type>(input, pos);

			while (pos < input.size()) {
				switch (input[pos]) {
				case ' ':
				case ',':
					++pos;
					break;
				case ']':
					++pos;
					return p; // End of array
				default:
					p.second = fromString<typename T::second_type>(input, pos);
					break;
				}
			}

			return p;
		}
		else {
			// These do not use syntax characters; should advance iterator until a syntax character is hit
			strv substr = getView(input, pos);

			if constexpr (std::is_same_v<T, bool>) {
				str toLower = futil::toLowerCase(substr);
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
				return std::stoi(substr.data());
			}
			else if constexpr (std::is_same_v<T, float>) {
				return std::stof(substr.data());
			}
			else if constexpr (std::is_same_v<T, double>) {
				return std::stod(substr.data());
			}
			else if constexpr (std::is_same_v<T, long>) {
				return std::stol(substr.data());
			}
			else if constexpr (std::is_same_v<T, long long>) {
				return std::stoll(substr.data());
			}
			else if constexpr (std::is_same_v<T, long double>) {
				return std::stold(substr.data());
			}
			else if constexpr (std::is_same_v<T, unsigned long>) {
				return std::stoul(substr.data());
			}
			else if constexpr (std::is_same_v<T, unsigned long long>) {
				return std::stoull(substr.data());
			}
			else if constexpr (c_enum<T>) {
				int ind = std::stoi(substr.data());
				return static_cast<T>(ind);
			}
			else if constexpr (c_keyed<T>) {
				return T::get(substr);
			}
		}
		return T();
	}

}