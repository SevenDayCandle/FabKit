export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.FTexture;
import fbc.FUtil;
import fbc.RBordered;
import fbc.RHorizontal;
import fbc.RVertical;
import fbc.StaticLoadables;

namespace fbc {
	export class CoreImages : public StaticLoadables {
	public:
		CoreImages(BaseContent& cnt) : StaticLoadables(cnt) {}

		FTexture& uiArrowIncrement = cacheTexture("UI/Arrow_Increment.png");
		FTexture& uiArrowLarge = cacheTexture("UI/Arrow_Large.png");
		FTexture& uiArrowSmall = cacheTexture("UI/Arrow_Small.png");
		FTexture& uiCheckboxEmpty = cacheTexture("UI/Checkbox_Empty.png");
		FTexture& uiCheckboxFilled = cacheTexture("UI/Checkbox_Filled.png");
		FTexture& uiClearLarge = cacheTexture("UI/Clear_Large.png");
		FTexture& uiClearSmall = cacheTexture("UI/Clear_Small.png");
		RBordered& uiDarkPanel = cacheBordered("UI/DarkPanelBase.png");
		RBordered& uiDarkPanelRound = cacheBordered("UI/DarkPanelRoundBase.png");
		RBordered& uiLargePanel = cacheBordered("UI/LargePanelBase.png");
		RBordered& uiLightPanel = cacheBordered("UI/LightPanelBase.png");
		RBordered& uiLightPanelRound = cacheBordered("UI/LightPanelRoundBase.png");
		RBordered& uiPanel = cacheBordered("UI/PanelBase.png");
		RBordered& uiPanelRound = cacheBordered("UI/PanelRoundBase.png");
		RBordered& uiThickPanel = cacheBordered("UI/ThickPanelBase.png");
		RHorizontal& uiSliderEmpty = cacheHorizontal("UI/SliderEmptyBase.png");
		RHorizontal& uiSliderFilled = cacheHorizontal("UI/SliderFilledBase.png");
		RVertical& uiScrollbar = cacheVertical("UI/ScrollbarBase.png");
		RVertical& uiScrollbutton = cacheVertical("UI/ScrollbuttonBase.png");
	};
}