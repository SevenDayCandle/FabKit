export module fbc.Cache;

import fbc.FUtil;
import fbc.ILoadable;
import std;

/* A lazy-initialized pointer that gets created when first invoked. Values can be used in const contexts */
export namespace fbc {
	export template <typename T> class Cache : public ILoadable {
	public:
		Cache(func<T*()> fetchFunc): fetchFunc(fetchFunc) {}
		~Cache() {Cache<T>::dispose();}

		operator T& () const { return get(); }

		void dispose() override;
		void reload() override;
		T& get() const;
	private:
		func<T*()> fetchFunc;
		mutable T* object = nullptr;
	};

	// Clear out the stored item
	template<typename T> void Cache<T>::dispose() {
		if (object != nullptr) {
			delete object;
		}
		object = nullptr;
	}

	// If the item was previously fetched, reload it. Does NOT fill in the object if it had not yet been fetched
	template<typename T> void Cache<T>::reload()
	{
		if (object != nullptr) {
			if constexpr (std::is_base_of_v<ILoadable, T>) {
				object->reload();
			}
			else {
				delete object;
				object = fetchFunc();
			}
		}
	}

	// Get the stored item, creating it if it does not exist
	template <typename T> T& Cache<T>::get() const {
		if (object == nullptr) {
			object = fetchFunc();
		}
		return *object;
	}
}