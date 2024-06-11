export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.RHorizontal;
import fbc.StaticLoadables;
import fbc.Cache;
import fbc.CoreConfig;
import fbc.EmptyDrawable;
import fbc.FTexture;
import fbc.FUtil;
import fbc.RVertical;
import std;

export namespace fbc {
	export class CoreImages : public StaticLoadables {
	public:
		CoreImages(BaseContent& cnt) : StaticLoadables(cnt) {}

		EmptyDrawable none = EmptyDrawable();

		FTexture& uiArrowIncrement = cacheTexture("UI/Arrow_Increment.png");
		FTexture& uiArrowLarge = cacheTexture("UI/Arrow_Large.png");
		FTexture& uiArrowSmall = cacheTexture("UI/Arrow_Small.png");
		FTexture& uiCheckboxEmpty = cacheTexture("UI/Checkbox_Empty.png");
		FTexture& uiCheckboxFilled = cacheTexture("UI/Checkbox_Filled.png");
		FTexture& uiClearLarge = cacheTexture("UI/Clear_Large.png");
		FTexture& uiClearSmall = cacheTexture("UI/Clear_Small.png");
		FTexture& uiDarkPanelBase = cacheTexture("UI/DarkPanelBase.png");
		FTexture& uiDarkPanelRoundBase = cacheTexture("UI/DarkPanelRoundBase.png");
		FTexture& uiLargePanelBase = cacheTexture("UI/LargePanelBase.png");
		FTexture& uiLightPanelBase = cacheTexture("UI/LightPanelBase.png");
		FTexture& uiLightPanelRoundBase = cacheTexture("UI/LightPanelRoundBase.png");
		FTexture& uiPanelBase = cacheTexture("UI/PanelBase.png");
		FTexture& uiPanelRoundBase = cacheTexture("UI/PanelRoundBase.png");
		FTexture& uiScrollbarBase = cacheTexture("UI/ScrollbarBase.png");
		FTexture& uiScrollbuttonBase = cacheTexture("UI/ScrollbuttonBase.png");
		FTexture& uiSliderEmptyBase = cacheTexture("UI/SliderEmptyBase.png");
		FTexture& uiSliderFilledBase = cacheTexture("UI/SliderFilledBase.png");
		FTexture& uiThickPanelBase = cacheTexture("UI/ThickPanelBase.png");

		RBordered& darkPanel = cacheBordered(uiDarkPanelBase);
		RBordered& darkPanelRound = cacheBordered(uiDarkPanelRoundBase);
		RBordered& largePanel = cacheBordered(uiLargePanelBase);
		RBordered& lightPanel = cacheBordered(uiLightPanelBase);
		RBordered& lightPanelRound = cacheBordered(uiLightPanelRoundBase);
		RBordered& panel = cacheBordered(uiPanelBase);
		RBordered& panelRound = cacheBordered(uiPanelRoundBase);
		RBordered& thickPanel = cacheBordered(uiThickPanelBase);
		RHorizontal& sliderEmpty = cacheHorizontal(uiSliderEmptyBase);
		RHorizontal& sliderFilled = cacheHorizontal(uiSliderFilledBase);
		RVertical& scrollbar = cacheVertical(uiScrollbarBase);
		RVertical& scrollbutton = cacheVertical(uiScrollbuttonBase);
	};
}