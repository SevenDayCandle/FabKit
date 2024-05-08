export module fbc.UIGrid;

import fbc.hitbox;
import fbc.uiBase;
import fbc.futil;

export namespace fbc {

	export template <c_ext<UIBase> T> class UIGrid : public UIBase {
	public:
		UIGrid(Hitbox* hb) : UIBase(hb) {}
		virtual ~UIGrid() {

		}

		template <c_itr<T> Iterable> UIGrid& addItems(Iterable& items);
		template <c_itr<T> Iterable> UIGrid& setItems(Iterable& items);
		virtual bool isHovered() override;
		virtual void renderImpl() override;
		virtual void updateImpl() override;
	protected:
		float spacing;
		int itemsPerRow;
		vec<uptr<T>> items;
	};
	template<c_ext<UIBase> T> bool UIGrid<T>::isHovered()
	{
		return futil::any(items, [](const uptr<UIBase>& i) { return i->isHovered(); });
	}
}