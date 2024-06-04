export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.RHorizontal;
import fbc.StaticImages;
import fbc.Cache;
import fbc.CoreConfig;
import fbc.FTexture;
import fbc.FUtil;
import fbc.RVertical;
import std;

export namespace fbc {
	export class CoreImages : public StaticImages {
	public:
		CoreImages(BaseContent& cnt) : StaticImages(cnt) {}

		FTexture& uiArrowIncrement = cacheTexture("UI/Arrow_Increment.png");
		FTexture& uiArrowLarge = cacheTexture("UI/Arrow_Large.png");
		FTexture& uiArrowSmall = cacheTexture("UI/Arrow_Small.png");
		FTexture& uiCheckboxEmpty = cacheTexture("UI/Checkbox_Empty.png");
		FTexture& uiCheckboxFilled = cacheTexture("UI/Checkbox_Filled.png");
		FTexture& uiClearLarge = cacheTexture("UI/Clear_Large.png");
		FTexture& uiClearSmall = cacheTexture("UI/Clear_Small.png");
		FTexture& uiHoverPanelBase = cacheTexture("UI/HoverPanelBase.png");
		FTexture& uiLargePanelBase = cacheTexture("UI/LargePanelBase.png");
		FTexture& uiLightPanelBase = cacheTexture("UI/LightPanelBase.png");
		FTexture& uiPanelBase = cacheTexture("UI/PanelBase.png");
		FTexture& uiScrollbarBase = cacheTexture("UI/ScrollbarBase.png");
		FTexture& uiScrollbuttonBase = cacheTexture("UI/ScrollbuttonBase.png");
		FTexture& uiSliderEmptyBase = cacheTexture("UI/SliderEmptyBase.png");
		FTexture& uiSliderFilledBase = cacheTexture("UI/SliderFilledBase.png");
		FTexture& uiThickPanelBase = cacheTexture("UI/ThickPanelBase.png");

		RBordered& hoverPanel = cacheBordered(uiHoverPanelBase);
		RBordered& largePanel = cacheBordered(uiLargePanelBase);
		RBordered& light = cacheBordered(uiLightPanelBase);
		RBordered& panel = cacheBordered(uiPanelBase);
		RBordered& thickPanel = cacheBordered(uiThickPanelBase);
		RHorizontal& sliderEmpty = cacheHorizontal(uiSliderEmptyBase);
		RHorizontal& sliderFilled = cacheHorizontal(uiSliderFilledBase);
		RVertical& scrollbar = cacheVertical(uiScrollbarBase);
		RVertical& scrollbutton = cacheVertical(uiScrollbuttonBase);
	};
}