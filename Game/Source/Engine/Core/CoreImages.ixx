export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.BorderedDrawable;
import fbc.BaseImages;
import fbc.Cache;
import fbc.CoreConfig;
import fbc.FTexture;
import fbc.FUtil;
import fbc.VerticalDrawable;
import std;

export namespace fbc {
	export class CoreImages : public BaseImages {
	public:
		CoreImages(BaseContent& cnt) : BaseImages(cnt) {
			hoverPanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(hoverPanelBase()); });
			largePanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(largePanelBase()); });
			panelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(panelBase()); });
			scrollbarCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbarBase()); });
			scrollbuttonCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbuttonBase()); });
		}

		inline BorderedDrawable& flatPanel() const { return *hoverPanelCache.get(); }
		inline BorderedDrawable& largePanel() const { return *largePanelCache.get(); }
		inline BorderedDrawable& panel() const { return *panelCache.get(); }
		inline VerticalDrawable& scrollbar() const { return *scrollbarCache.get(); }
		inline VerticalDrawable& scrollbutton() const { return *scrollbuttonCache.get(); }

		inline FTexture& arrowLarge() { return getTexture("UI/Arrow_Large.png"); };
		inline FTexture& arrowSmall() { return getTexture("UI/Arrow_Small.png"); };
		inline FTexture& checkboxEmpty() { return getTexture("UI/Checkbox_Empty.png"); };
		inline FTexture& checkboxFilled() { return getTexture("UI/Checkbox_Filled.png"); };
		inline FTexture& hoverPanelBase() { return getTexture("UI/HoverPanelBase.png"); };
		inline FTexture& largePanelBase() { return getTexture("UI/LargePanelBase.png"); };
		inline FTexture& lightPanelBase() { return getTexture("UI/LightPanelBase.png"); };
		inline FTexture& panelBase() { return getTexture("UI/PanelBase.png"); };
		inline FTexture& scrollbarBase() { return getTexture("UI/ScrollbarBase.png"); };
		inline FTexture& scrollbuttonBase() { return getTexture("UI/ScrollbuttonBase.png"); };
		inline FTexture& thickPanelBase() { return getTexture("UI/ThickPanelBase.png"); };
	private:
		uptr<Cache<BorderedDrawable>> hoverPanelCache;
		uptr<Cache<BorderedDrawable>> largePanelCache;
		uptr<Cache<VerticalDrawable>> scrollbarCache;
		uptr<Cache<VerticalDrawable>> scrollbuttonCache;
		uptr<Cache<BorderedDrawable>> panelCache;
	};
}