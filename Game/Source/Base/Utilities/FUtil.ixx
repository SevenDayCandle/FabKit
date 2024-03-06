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

	export template <typename T, typename Pred> bool all(T container, Pred predicate) {
		return std::all_of(container.begin(), container.end(), predicate);
	}

	export template <typename T, typename Pred> bool any(T container, Pred predicate) {
		return std::any_of(container.begin(), container.end(), predicate);
	}
}