export module fbc.UIGrid;

import fbc.CoreConfig;
import fbc.Hitbox;
import fbc.UIBase;
import fbc.UIVerticalScrollbar;
import fbc.FUtil;
import fbc.ScaleHitbox;
import std;

export namespace fbc {

	export template <c_ext<UIBase> T> class UIGrid : public UIBase {
	public:
		UIGrid(Hitbox* hb, float scrollSpeed = 1) : UIBase(hb),
			scrollSpeed(scrollSpeed),
			scrollbar{ new ScaleHitbox(hb->w * 0.93f / cfg.renderScale(), hb->y + hb->h * 0.05f / cfg.renderScale(), 48, hb->h * 0.9f / cfg.renderScale()) } {
			scrollbar.enabled = false;
		}
		virtual ~UIGrid() {

		}

		inline int size() { return items.size(); }

		template <c_itr<uptr<T>> Iterable> UIGrid& addItems(const Iterable& added);
		template <c_itr<uptr<T>> Iterable> UIGrid& setItems(const Iterable& items);
		UIGrid& addItem(uptr<T> item);
		virtual bool isHovered() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		float scrollSpeed;
		float spacingX;
		float spacingY;
		UIVerticalScrollbar scrollbar;
		vec<uptr<T>> items;

		void updateItemOffsets();
		void updateItemOffsets(int begin, int end);
	};

	template<c_ext<UIBase> T> bool UIGrid<T>::isHovered()
	{
		return futil::any(items, [](const uptr<UIBase>& i) { return i->isHovered(); });
	}

	template<c_ext<UIBase> T> void UIGrid<T>::renderImpl()
	{
		for (const uptr<UIBase>& item : items) {
			item->render();
		}
		scrollbar.render();
	}

	template<c_ext<UIBase> T> void UIGrid<T>::updateImpl()
	{
		UIBase::updateImpl();
		for (const uptr<UIBase>& item : items) {
			item->update();
		}
		scrollbar.update();
	}

	// Updates the positions of ALL items in the grid, and shows the scrollbar if any of them would extend outside of the grid
	template<c_ext<UIBase> T> void UIGrid<T>::updateItemOffsets()
	{
		float x = hb->x;
		float y = hb->y;
		for (const uptr<UIBase>& item : items) {
			item->hb->setExactPos(x, y);

			x += spacingX;
			if (x >= hb->x + hb->w) {
				x = hb->x;
				y += spacingY;
			}
		}

		scrollbar.enabled = y > hb->y + hb->h;
	}

	// Updates the positions of items from index begin (inclusive) to index end (exclusive), and shows the scrollbar if any of them would extend outside of the grid
	template<c_ext<UIBase> T> void UIGrid<T>::updateItemOffsets(int begin, int end) {
		int rowsize = hb->w / spacingX;
		int xP = begin % rowsize;
		int yP = begin / rowsize; // Intentional integer division in parentheses to ensure that this multiplier rounds down
		float x = hb->x + spacingX * xP;
		float y = hb->y + spacingY * yP;
		for (int i = begin; i < end; ++i) {
			items[i]->hb->setExactPos(x, y);

			x += spacingX;
			if (x >= hb->x + hb->w) {
				x = hb->x;
				y += spacingY;
			}
		}

		scrollbar.enabled = y > hb->y + hb->h;
	}

	// Add a singular item to the list
	template<c_ext<UIBase> T> UIGrid<T>& UIGrid<T>::addItem(uptr<T> item)
	{
		this->items.push_back(std::move(item));
		updateItemOffsets(this->items.size() - 1, this->items.size());
		return *this;
	}

	// Appends items to the end of the grid
	template<c_ext<UIBase> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::addItems(const Iterable& added) {
		int a = this->items.size();
		this->items.insert(this->items.end(),
			std::make_move_iterator(added.begin()),
			std::make_move_iterator(added.end()));
		int b = this->items.size();
		updateItemOffsets(a, b);
		return *this;
	}

	// Replaces the contents of the grid with the incoming items
	template<c_ext<UIBase> T> template<c_itr<uptr<T>> Iterable> UIGrid<T>& UIGrid<T>::setItems(const Iterable& items)
	{
		this->items = std::move(items);
		updateItemOffsets();
		return *this;
	}
}