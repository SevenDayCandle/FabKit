export module fbc.futil;

import std;

// std shorthands
export template <typename T> using deque = std::deque<T>;
export template <typename T> using list = std::list<T>;
export template <typename T> using set = std::set<T>;
export template <typename T> using span = std::span<T>;
export template <typename T> using sptr = std::shared_ptr<T>;
export template <typename T> using uptr = std::unique_ptr<T>;
export template <typename T> using uset = std::unordered_set<T>;
export template <typename T> using vec = std::vector<T>;
export template <typename T, size_t U> using arr = std::array<T, U>;
export template <typename T, typename U> using map = std::map<T, U>;
export template <typename T, typename U> using pair = std::pair<T, U>;
export template <typename T, typename U> using unmap = std::unordered_map<T, U>;
export template <typename R, typename... Args > using func = std::function<R>;
export using str = std::string;
export using path = std::filesystem::path;

export namespace fbc {
	const str JSON_EXT = ".json";

	export template <typename T> T read_file_json(T input, str path);
	export template <typename T> T read_json(str input);
	export template <typename T> str write_file_json(T input, str path);
	export template <typename T> str write_json(T input);
}