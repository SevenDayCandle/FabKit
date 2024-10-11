export module fbc.SelectView;

import fbc.FUtil;
import fbc.UIEntry;
import std;

namespace fbc {
	export template <typename T> class SelectView : public std::ranges::view_interface<SelectView<T>> {
	public:
		class SelectIterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			SelectIterator() {}
			SelectIterator(const SelectView<T>* view, set<int>::iterator it): view(view), it(it) {}

			reference operator*() const { return *(view->rows[*it]); }
			pointer operator->() const { return (view->rows[*it].get()); }

			SelectIterator& operator++() { return ++it, * this; }
			SelectIterator operator++(int) {
				SelectIterator tmp = *this;
				++it;
				return tmp;
			}

			friend bool operator==(const SelectIterator& a, const SelectIterator& b) { return a.it == b.it; }
			friend bool operator!=(const SelectIterator& a, const SelectIterator& b) { return a.it != b.it; }

		private:
			const SelectView<T>* view;
			set<int>::iterator it;
		};

		SelectView(set<int>& inds, vec<uptr<T>>& rows) : inds(inds), rows(rows) {}

		inline SelectIterator begin() { return SelectIterator(this, inds.begin()); }
		inline SelectIterator begin() const { return SelectIterator(this, inds.begin()); }
		inline SelectIterator end() { return SelectIterator(this, inds.end()); }
		inline SelectIterator end() const { return SelectIterator(this, inds.end()); }
		inline size_t size() const { return inds.size(); }
	private:
		set<int>& inds;
		vec<uptr<T>>& rows;
	};

	export template <typename T> using EntryView = SelectView<UIEntry<T>>;
}

