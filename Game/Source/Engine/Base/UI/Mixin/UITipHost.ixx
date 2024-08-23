export module fbc.UITipHost;

import fbc.FUtil;
import fbc.FWindow;
import fbc.GenericTip;
import fbc.Hitbox;
import fbc.Hoverable;
import fbc.Tooltip;

namespace fbc {
	export template <c_ext<Hoverable> T> class UITipHost : public Hoverable {
	public:
		UITipHost(T&& item, GenericTip* tooltip) : ui(forward<T>(item)), tooltip(tooltip), Hoverable(item.win) {}
		UITipHost(T&& item, strv text) : ui(forward<T>(item)), ownedTip(new Tooltip(item.win, text)), Hoverable(item.win) {
			this->tooltip = ownedTip.get();
		}

		GenericTip* tooltip;
		T ui;

		operator T* () { return &ui; }
		operator T& () { return ui; }

		virtual void refreshDimensions() override;
		virtual void updateImpl() override;

		inline Hitbox* getHb() final override { return ui.getHb(); }
		inline UITipHost& makeOwnedTip(strv text) { return makeOwnedTip(make_unique<Tooltip>(win, text)); }
		inline virtual UITipHost& setTooltip(GenericTip* tooltip) { return this->tooltip = tooltip, *this; } // Assigns a non-owned tooltip to this object

		UITipHost& makeOwnedTip(uptr<GenericTip>&& tooltip);
	private:
		uptr<GenericTip> ownedTip;
	};

	template<c_ext<Hoverable> T> void UITipHost<T>::refreshDimensions()
	{
		ui.refreshDimensions();
		if (tooltip) {
			tooltip->refreshDimensions();
		}
	}

	template<c_ext<Hoverable> T> void UITipHost<T>::updateImpl()
	{
		ui.updateImpl();
		if (ui.getHb()->isHovered() && tooltip) {
			tooltip->queue();
		}
	}

	// Assigns an owned tooltip to this object (i.e. a tooltip that gets destroyed when this object is destroyed)
	template<c_ext<Hoverable> T> UITipHost<T>& UITipHost<T>::makeOwnedTip(uptr<GenericTip>&& tooltip)
	{
		ownedTip = move(tooltip);
		this->tooltip = ownedTip.get();
		return *this;
	}
}