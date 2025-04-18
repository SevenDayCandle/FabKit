export module fab.FUtil;

import fab.KeyedItem;
import std;

namespace fab {
	constexpr std::string_view VOID_TYPESTR = "void";

	// Hasing structure for string_view lookup on str containers
	export struct str_hash
	{
		using hash_type = std::hash<std::string_view>;
		using is_transparent = void;

		std::size_t operator()(const char* str) const { return hash_type{}(str); }
		std::size_t operator()(std::string_view str) const { return hash_type{}(str); }
		std::size_t operator()(std::string const& str) const { return hash_type{}(str); }
	};

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
	export template<typename T> concept c_ptr = std::is_pointer_v<T>;
	export template<typename T> concept c_push = requires(T t, typename T::value_type v) {
		{ t.push_back(v) } -> std::same_as<void>;
	};
	export template<typename T> concept c_ref = std::is_reference_v<T>;
	export template<typename T> concept c_refw = is_specialization_v<T, std::reference_wrapper>;
	export template<typename It, typename T> concept c_set = c_itr<T, It>&& requires(It a, T v) {
		{ a.find(v) } -> std::convertible_to<typename It::iterator>;
	};
	export template<typename T> concept c_str = requires(T t) {
		std::string_view{ t };
	};
	export template<typename T> concept c_tuple = is_specialization_v<T, std::tuple>;
	export template<typename T, typename... Args> concept c_varg = (std::same_as<T, Args> && ...);;
	export template<typename T> concept c_vec = is_specialization_v<T, std::vector>;

	// std shorthands. Sorry peeps
	export template <typename R> using func = std::function<R>;
	export template <typename T, class Comp = std::less<T>, class Alloc = std::allocator<T>> using mset = std::multiset<T, Comp, Alloc>;
	export template <typename T, class Hash = std::hash<T>, class Eq = std::equal_to<T>, class Alloc = std::allocator<T>> using uset = std::unordered_set<T, Hash, Eq, Alloc>;
	export template <typename T, size_t U> using arr = std::array<T, U>;
	export template <typename T, typename U, class Comp = std::less<T>, class Alloc = std::allocator<std::pair<const T, U>>> using map = std::map<T, U, Comp, Alloc>;
	export template <typename T, typename U, class Hash = std::hash<T>, class Eq = std::equal_to<T>, class Alloc = std::allocator<std::pair<const T, U>>> using umap = std::unordered_map<T, U, Hash, Eq, Alloc>;
	export template <typename T, typename U> using pair = std::pair<T, U>;
	export template <typename T> using dec_t = std::decay_t<T>;
	export template <typename T> using ilist = std::initializer_list<T>;
	export template <typename T> using opt = std::optional<T>;
	export template <typename T> using pqueue_max = std::priority_queue<T>;
	export template <typename T> using pqueue_min = std::priority_queue<T, std::vector<T>, std::greater<T>>;
	export template <typename T> using ref = std::reference_wrapper<T>;
	export template <typename T> using sptr = std::shared_ptr<T>;
	export template <typename T> using strumap = umap<std::string, T, str_hash, std::equal_to<>>;
	export template <typename T> using uptr = std::unique_ptr<T>;
	export template <typename T> using vec = std::vector<T>;
	export using cstr = const char[];
	export using dir_entry = std::filesystem::directory_entry;
	export using dir_itr = std::filesystem::directory_iterator;
	export using file_type = std::filesystem::file_type;
	export using int32 = std::int32_t;
	export using path = std::filesystem::path;
	export using str = std::string;
	export using strv = std::string_view;
	export using uint16 = std::uint16_t;
	export using uint32 = std::uint32_t;
	export using uint64 = std::uint64_t;
	export using uint8 = std::uint8_t;

	export using std::any;
	export using std::deque;
	export using std::exception;
	export using std::hash;
	export using std::invoke_result_t;
	export using std::list;
	export using std::queue;
	export using std::ranges::range_value_t;
	export using std::ranges::ref_view;
	export using std::ranges::transform_view;
	export using std::set;
	export using std::span;
	export using std::type_index;
	export using std::type_info;

	export using std::forward;
	export using std::make_shared;
	export using std::make_unique;
	export using std::move;

	// Adapted from https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/64490578#64490578
	template <typename T> constexpr strv _funcsigimpl() { return std::source_location::current().function_name(); }
	export template <typename T> constexpr strv nameof() {
		constexpr strv fname = _funcsigimpl<T>();
		constexpr strv vname = _funcsigimpl<void>();
		constexpr size_t prefix_length = vname.find(VOID_TYPESTR);
		constexpr size_t suffix_length = vname.length() - prefix_length - VOID_TYPESTR.length();
		constexpr strv clname = fname.substr(prefix_length, fname.length() - prefix_length - suffix_length);
		size_t pos = clname.rfind(' ');
		return pos == strv::npos ? clname : clname.substr(pos + 1);
	}
}

// Utility functions
namespace fab::futil {
	export constexpr int INT_MAX = std::numeric_limits<int>::max();
	export constexpr int INT_MIN = std::numeric_limits<int>::min();
	export constexpr strv BLANK = "";
	export constexpr strv FBC = "fab";
	export constexpr strv JSON_EXT = ".json";
	export constexpr strv MODS = "mods";
	export constexpr strv VAL_FALSE = "false";
	export constexpr strv VAL_FALSE_NUM = "0";
	export constexpr strv VAL_TRUE = "true";
	export constexpr strv VAL_TRUE_NUM = "1";

	export bool isNumeric(strv text);
	export bool isPrefix(strv source, strv prefix);
	export float fastLerp(float start, float end, float t) noexcept;
	export str dimensionString(const pair<int, int>& p);
	export str dimensionString(int x, int y);
	export str toLowerCase(strv input);
	export str toUpperCase(strv input);
	export str unescape(strv input, size_t& pos);
	export str& toLowerCaseInPlace(str& input);
	export str& toUpperCaseInPlace(str& input);
	export strv getView(strv input, size_t& pos);
	export template <c_itr<strv> SCo> str joinStr(strv delimiter, SCo items);
	export template <typename T, c_itr<uptr<T>> TCo> vec<uptr<T>> vecCopy(const TCo& container);
	export template <typename T, c_itr<T> TCo> bool has(const TCo& container, const T& value);
	export template <typename T, c_itr<T> TCo> const T* find(const TCo& container, const T& value);
	export template <typename T> str toString(const T& obj);
	export template <typename T> str toStringWrapped(const T& obj);
	export template <typename T> T fromString(strv input);
	export template <typename T> T fromString(strv input, size_t& pos);
	export template <typename TCo, typename Func> requires std::ranges::range<TCo> && c_invc<Func, range_value_t<TCo>, strv> str joinStrMap(strv delimiter, const TCo& items, Func strFunc);
	export template <typename TCo, typename Func> requires c_itr<TCo, typename TCo::value_type> && c_invc<Func, typename TCo::value_type, invoke_result_t<Func, typename TCo::value_type>> vec<invoke_result_t<Func, typename TCo::value_type>> transform(const TCo& container, Func mapFunc);
	export template <typename TCo, typename Func> requires c_map_of<TCo, typename TCo::key_type, typename TCo::mapped_type> && c_invc<Func, typename TCo::mapped_type, invoke_result_t<Func, typename TCo::mapped_type>> map<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> transformMap(const TCo& src, Func mapFunc);
	export template <typename TCo, typename Func> requires c_map_of<TCo, typename TCo::key_type, typename TCo::mapped_type>&& c_invc<Func, typename TCo::mapped_type, invoke_result_t<Func, typename TCo::mapped_type>> umap<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> transformUmap(const TCo& src, Func mapFunc);
}

/*
 * IMPLEMENTATIONS
 */

namespace fab::futil {
	// Format a pair as a dimension
	str dimensionString(int x, int y) {
		return std::to_string(x) + "x" + std::to_string(y);
	}

	str dimensionString(const pair<int,int>& p) {
		return dimensionString(p.first, p.second);
	}

	// Checks if a string-like starts with another string-like
	bool isPrefix(strv source, strv prefix) {
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

	// Variant of std::lerp for floats without bounds checking and with lower precision
	float fastLerp(float start, float end, float t) noexcept {
		return (1 - t) * start + t * end;
	}

	// Create a lowercase version of a string-like
	str toLowerCase(strv input) {
		str res(input.size(), '\0');
		std::ranges::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return res;
	}

	// Modify an existing string to be lowercase
	str& toLowerCaseInPlace(str& input) {
		std::ranges::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return input;
	}

	// Create an uppercase version of a string-like
	str toUpperCase(strv input) {
		str res(input.size(), '\0');
		std::ranges::transform(input.begin(), input.end(), res.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return res;
	}

	// Modify an existing string to be uppercase
	str& toUpperCaseInPlace(str& input) {
		std::ranges::transform(input.begin(), input.end(), input.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return input;
	}

	// Find the first item in the container that matches the given value
	template<typename T, c_itr<T> TCo> const T* find(const TCo& container, const T& value) {
		if constexpr (c_set<T, TCo>) {
			auto it = container.find(value);
			if (it != container.end()) {
				return &(*it);
			}
		}
		else {
			auto it = std::find(container.begin(), container.end(), value);
			if (it != container.end()) {
				return &(*it);
			}
		}
		return nullptr;
	}

	// Check whether the given container contains the given value
	template<typename T, c_itr<T> TCo> bool has(const TCo& container, const T& value) {
		const T* res = find<T, TCo>(container, value);
		return res != nullptr;
	}

	// Check whether the text can be converted into a number
	bool isNumeric(strv text) {
		return !text.empty() && std::ranges::all_of(text, [](unsigned char c) {return std::isdigit(c); });
	}

	// Join a collection of strings with a delimiter
	template<c_itr<strv> SCo> str joinStr(strv delimiter, SCo items) {
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

	// Create a deep copy of an iterable of unique pointers
	template<typename T, c_itr<uptr<T>> TCo> vec<uptr<T>> vecCopy(const TCo& container) {
		vec<T> res(container.size());
		std::transform(container.begin(), container.end(), res.begin(), [](const uptr<T>& ptr) { return make_unique<T>(*ptr); });
		return res;
	}

	// Represent a collection of objects as a joined string with a delimiter
	template<typename TCo, typename Func> requires std::ranges::range<TCo>&& c_invc<Func, range_value_t<TCo>, strv> str joinStrMap(strv delimiter, const TCo& items, Func strFunc)
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
	template <typename TCo, typename Func> requires c_itr<TCo, typename TCo::value_type> && c_invc<Func, typename TCo::value_type, invoke_result_t<Func, typename TCo::value_type>> vec<invoke_result_t<Func, typename TCo::value_type>> transform(const TCo& container, Func mapFunc) {
		vec<invoke_result_t<Func, typename TCo::value_type>> res(container.size());
		std::transform(container.begin(), container.end(), res.begin(), mapFunc);
		return res;
	}

	// Transform each of the values in the map into a new map
	template<typename TCo, typename Func> requires c_map_of<TCo, typename TCo::key_type, typename TCo::mapped_type>&& c_invc<Func, typename TCo::mapped_type, invoke_result_t<Func, typename TCo::mapped_type>> map<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> transformMap(const TCo& src, Func mapFunc) {
		map<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> res;
		for (const auto& p : src) {
			res[p.first] = mapFunc(p.second);
		}
		return res;
	}

	// Transform each of the values in the map into a new unordered map
	export template<typename TCo, typename Func> requires c_map_of<TCo, typename TCo::key_type, typename TCo::mapped_type>&& c_invc<Func, typename TCo::mapped_type, invoke_result_t<Func, typename TCo::mapped_type>> umap<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> transformUmap(const TCo& src, Func mapFunc) {
		umap<typename TCo::key_type, invoke_result_t<Func, typename TCo::mapped_type>> res;
		for (const auto& p : src) {
			res[p.first] = mapFunc(p.second);
		}
		return res;
	}

	// Attempt to convert an arbitrary object into a regular string representation
	template <typename T> str toString(const T& obj) {
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
		else if constexpr (c_ptr<T>) {
			return obj ? toString(*obj) : "";
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
		else if constexpr (c_refw<T>) {
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
		else if constexpr (c_tuple<T>) {
			std::string result = "[";
			std::apply([&result](const auto&... elems) {
				((result += toStringWrapped(elems) + ", "), ...);
				if (!result.empty()) {
					result.pop_back();
					result.pop_back();
				}
				}, obj);
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
	template <typename T> str toStringWrapped(const T& obj) {
		if constexpr (std::is_same_v<T, str>) {
			return '"' + obj + '"';
		}
		if constexpr (c_str<T>) {
			return '"' + obj + '"';
		}
		if constexpr (c_refw<T>) {
			return toStringWrapped(obj.get());
		}
		return toString(obj);
	}

	// For types that do not use syntax characters, we can safely treat everything in between this pos and the next syntax character as being part of the object to be deserialized
	strv getView(strv input, size_t& pos)
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
	str unescape(strv input, size_t& pos) {
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
	// TODO handle maps
	template <typename T> T fromString(strv input) {
		size_t pos = 0;
		return fromString<T>(input, pos);
	}

	template <typename T> T fromString(strv input, size_t& pos) {
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
					res.push_back(fromString<typename T::value_type>(input, pos));
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
				if (toLower == VAL_TRUE || toLower == VAL_TRUE_NUM) {
					return true;
				}
				else if (toLower == VAL_FALSE || toLower == VAL_FALSE_NUM) {
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
			else if constexpr (c_ref<T> && c_keyed<std::remove_reference_t<T>>) {
				return std::remove_reference_t<T>::forceGet(substr);
			}
			else if constexpr (c_ptr<T> && c_keyed<std::remove_pointer_t<T>>) {
				return std::remove_pointer_t<T>::get(substr);
			}
		}
		return T();
	}

}