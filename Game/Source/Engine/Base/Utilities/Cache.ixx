export module fbc.Cache;

import fbc.FUtil;

/* A lazy-initialized pointer that gets created when first invoked. Values can be used in const contexts */
export namespace fbc {
	export template <typename T> class Cache {
	public:
		Cache(func<T*()> fetchFunc): fetchFunc(fetchFunc) {}
		~Cache() {
			if (object) {
				delete object;
			}
		}

		T& get() const {
			if (object == nullptr) {
				object = fetchFunc();
			}
			return *object;
		}
		operator T&() const {return get();}
	private:
		func<T*()> fetchFunc;
		mutable T* object = nullptr;
	};
}