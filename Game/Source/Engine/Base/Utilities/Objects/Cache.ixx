export module fbc.cache;

import fbc.futil;
import std;

export namespace fbc {
	export template <typename T> class Cache {
	public:
		Cache(func<T()> fetchFunc): fetchFunc(fetchFunc) {}

		T& get() {
			if (object == nullptr) {
				object = std::make_unique<T>(fetchFunc());
			}
			return *object;
		}
		operator T&() {
			return get();
		}
	private:
		func<T()> fetchFunc;
		uptr<T> object;
	};
}