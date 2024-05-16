export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.RBordered;
import fbc.RHorizontal;
import fbc.BaseImages;
import fbc.Cache;
import fbc.CoreConfig;
import fbc.FTexture;
import fbc.FUtil;
import fbc.RVertical;
import std;

export namespace fbc {
	export class CoreImages : public BaseImages {
	public:
		CoreImages(BaseContent& cnt) : BaseImages(cnt) {}

		const Cache<FTexture> uiArrowLarge = cacheTexture("UI/Arrow_Large.png");
		const Cache<FTexture> uiArrowSmall = cacheTexture("UI/Arrow_Small.png");
		const Cache<FTexture> uiCheckboxEmpty = cacheTexture("UI/Checkbox_Empty.png");
		const Cache<FTexture> uiCheckboxFilled = cacheTexture("UI/Checkbox_Filled.png");
		const Cache<FTexture> uiHoverPanelBase = cacheTexture("UI/HoverPanelBase.png");
		const Cache<FTexture> uiLargePanelBase = cacheTexture("UI/LargePanelBase.png");
		const Cache<FTexture> uiLightPanelBase = cacheTexture("UI/LightPanelBase.png");
		const Cache<FTexture> uiPanelBase = cacheTexture("UI/PanelBase.png");
		const Cache<FTexture> uiScrollbarBase = cacheTexture("UI/ScrollbarBase.png");
		const Cache<FTexture> uiScrollbuttonBase = cacheTexture("UI/ScrollbuttonBase.png");
		const Cache<FTexture> uiSliderEmptyBase = cacheTexture("UI/SliderEmptyBase.png");
		const Cache<FTexture> uiSliderFilledBase = cacheTexture("UI/SliderFilledBase.png");
		const Cache<FTexture> uiThickPanelBase = cacheTexture("UI/ThickPanelBase.png");

		const Cache<RBordered> hoverPanel = cacheBordered(uiHoverPanelBase);
		const Cache<RBordered> largePanel = cacheBordered(uiLargePanelBase);
		const Cache<RBordered> panel = cacheBordered(uiPanelBase);
		const Cache<RHorizontal> sliderEmpty = cacheHorizontal(uiSliderEmptyBase);
		const Cache<RHorizontal> sliderFilled = cacheHorizontal(uiSliderFilledBase);
		const Cache<RVertical> scrollbar = cacheVertical(uiScrollbarBase);
		const Cache<RVertical> scrollbutton = cacheVertical(uiScrollbuttonBase);
	};
}