export module fbc.CoreImages;

import fbc.BaseContent;
import fbc.BorderedDrawable;
import fbc.BaseImages;
import fbc.Cache;
import fbc.CoreConfig;
import fbc.FTexture;
import fbc.futil;
import fbc.VerticalDrawable;
import std;

export namespace fbc {
	export class CoreImages : public BaseImages {
	public:
		CoreImages(BaseContent& cnt) : BaseImages(cnt) {
			flatPanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(flatPanelCenter(), flatPanelBorderB(), flatPanelBorderL(), flatPanelBorderR(), flatPanelBorderT(), flatPanelCornerBL(), flatPanelCornerBR(), flatPanelCornerTL(), flatPanelCornerTR()); });
			largePanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(largePanelCenter(), largePanelBorderB(), largePanelBorderL(), largePanelBorderR(), largePanelBorderT(), largePanelCornerBL(), largePanelCornerBR(), largePanelCornerTL(), largePanelCornerTR()); });
			smallPanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(smallPanelCenter(), smallPanelBorderB(), smallPanelBorderL(), smallPanelBorderR(), smallPanelBorderT(), smallPanelCornerBL(), smallPanelCornerBR(), smallPanelCornerTL(), smallPanelCornerTR()); });
			scrollbarCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbarCenter(), scrollbarBorderB(), scrollbarBorderT()); });
			scrollbuttonCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbuttonCenter(), scrollbuttonBorderB(), scrollbuttonBorderT()); });
		}

		inline BorderedDrawable& flatPanel() const { return *flatPanelCache.get(); }
		inline BorderedDrawable& largePanel() const { return *largePanelCache.get(); }
		inline BorderedDrawable& smallPanel() const { return *smallPanelCache.get(); }
		inline VerticalDrawable& scrollbar() const { return *scrollbarCache.get(); }
		inline VerticalDrawable& scrollbutton() const { return *scrollbuttonCache.get(); }

		inline FTexture& arrowLarge() { return getTexture("UI/Arrow_Large.png"); };
		inline FTexture& arrowSmall() { return getTexture("UI/Arrow_Small.png"); };
		inline FTexture& checkboxEmpty() { return getTexture("UI/Checkbox_Empty.png"); };
		inline FTexture& checkboxFilled() { return getTexture("UI/Checkbox_Filled.png"); };
		inline FTexture& flatPanelBorderB() { return getTexture("UI/FlatPanel_Border_B.png"); };
		inline FTexture& flatPanelBorderL() { return getTexture("UI/FlatPanel_Border_L.png"); };
		inline FTexture& flatPanelBorderR() { return getTexture("UI/FlatPanel_Border_R.png"); };
		inline FTexture& flatPanelBorderT() { return getTexture("UI/FlatPanel_Border_T.png"); };
		inline FTexture& flatPanelCenter() { return getTexture("UI/FlatPanel_Center.png"); };
		inline FTexture& flatPanelCornerBL() { return getTexture("UI/FlatPanel_Corner_BL.png"); };
		inline FTexture& flatPanelCornerBR() { return getTexture("UI/FlatPanel_Corner_BR.png"); };
		inline FTexture& flatPanelCornerTL() { return getTexture("UI/FlatPanel_Corner_TL.png"); };
		inline FTexture& flatPanelCornerTR() { return getTexture("UI/FlatPanel_Corner_TR.png"); };
		inline FTexture& largePanelBorderB() { return getTexture("UI/LargePanel_Border_B.png"); };
		inline FTexture& largePanelBorderL() { return getTexture("UI/LargePanel_Border_L.png"); };
		inline FTexture& largePanelBorderR() { return getTexture("UI/LargePanel_Border_R.png"); };
		inline FTexture& largePanelBorderT() { return getTexture("UI/LargePanel_Border_T.png"); };
		inline FTexture& largePanelCenter() { return getTexture("UI/LargePanel_Center.png"); };
		inline FTexture& largePanelCornerBL() { return getTexture("UI/LargePanel_Corner_BL.png"); };
		inline FTexture& largePanelCornerBR() { return getTexture("UI/LargePanel_Corner_BR.png"); };
		inline FTexture& largePanelCornerTL() { return getTexture("UI/LargePanel_Corner_TL.png"); };
		inline FTexture& largePanelCornerTR() { return getTexture("UI/LargePanel_Corner_TR.png"); };
		inline FTexture& scrollbarBorderB() { return getTexture("UI/Scrollbar_Border_B.png"); }
		inline FTexture& scrollbarBorderT() { return getTexture("UI/Scrollbar_Border_T.png"); }
		inline FTexture& scrollbarCenter() { return getTexture("UI/Scrollbar_Center.png"); }
		inline FTexture& scrollbuttonBorderB() { return getTexture("UI/Scrollbutton_Border_B.png"); }
		inline FTexture& scrollbuttonBorderT() { return getTexture("UI/Scrollbutton_Border_T.png"); }
		inline FTexture& scrollbuttonCenter() { return getTexture("UI/Scrollbutton_Center.png"); }
		inline FTexture& smallPanelBorderB() { return getTexture("UI/SmallPanel_Border_B.png"); };
		inline FTexture& smallPanelBorderL() { return getTexture("UI/SmallPanel_Border_L.png"); };
		inline FTexture& smallPanelBorderR() { return getTexture("UI/SmallPanel_Border_R.png"); };
		inline FTexture& smallPanelBorderT() { return getTexture("UI/SmallPanel_Border_T.png"); };
		inline FTexture& smallPanelCenter() { return getTexture("UI/SmallPanel_Center.png"); };
		inline FTexture& smallPanelCornerBL() { return getTexture("UI/SmallPanel_Corner_BL.png"); };
		inline FTexture& smallPanelCornerBR() { return getTexture("UI/SmallPanel_Corner_BR.png"); };
		inline FTexture& smallPanelCornerTL() { return getTexture("UI/SmallPanel_Corner_TL.png"); };
		inline FTexture& smallPanelCornerTR() { return getTexture("UI/SmallPanel_Corner_TR.png"); };
		inline FTexture& squareButton() { return getTexture("UI/SquareButton.png"); };
	private:
		uptr<Cache<BorderedDrawable>> flatPanelCache;
		uptr<Cache<BorderedDrawable>> largePanelCache;
		uptr<Cache<VerticalDrawable>> scrollbarCache;
		uptr<Cache<VerticalDrawable>> scrollbuttonCache;
		uptr<Cache<BorderedDrawable>> smallPanelCache;
	};
}