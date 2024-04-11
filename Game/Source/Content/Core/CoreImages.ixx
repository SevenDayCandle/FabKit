export module fbc.coreImages;

import fbc.baseContent;
import fbc.borderedDrawable;
import fbc.baseImages;
import fbc.cache;
import fbc.coreConfig;
import fbc.ftexture;
import fbc.futil;
import fbc.verticalDrawable;
import std;

export namespace fbc {
	export class CoreImages : public BaseImages {
	public:
		CoreImages(BaseContent& cnt) : BaseImages(cnt) {
			panelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(panelCenter(), panelBorderB(), panelBorderL(), panelBorderR(), panelBorderT(), panelCornerBL(), panelCornerBR(), panelCornerTL(), panelCornerTR()); });
			smallPanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(panelCenter(), smallPanelBorderB(), smallPanelBorderL(), smallPanelBorderR(), smallPanelBorderT(), smallPanelCornerBL(), smallPanelCornerBR(), smallPanelCornerTL(), smallPanelCornerTR()); });
			scrollbarCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbarCenter(), scrollbarBorderB(), scrollbarBorderT()); });
			scrollbuttonCache = std::make_unique<Cache<VerticalDrawable>>([this]() {return VerticalDrawable(scrollbuttonCenter(), scrollbuttonBorderB(), scrollbuttonBorderT()); });
		}

		inline BorderedDrawable& panel() { return *panelCache.get(); }
		inline BorderedDrawable& smallPanel() { return *smallPanelCache.get(); }
		inline VerticalDrawable& scrollbar() { return *scrollbarCache.get(); }
		inline VerticalDrawable& scrollbutton() { return *scrollbuttonCache.get(); }

		inline FTexture& checkboxEmpty() { return getTexture("UI/Checkbox_Empty.png"); };
		inline FTexture& checkboxFilled() { return getTexture("UI/Checkbox_Filled.png"); };
		inline FTexture& panelBorderB() { return getTexture("UI/Panel_Border_B.png"); };
		inline FTexture& panelBorderL() { return getTexture("UI/Panel_Border_L.png"); };
		inline FTexture& panelBorderR() { return getTexture("UI/Panel_Border_R.png"); };
		inline FTexture& panelBorderT() { return getTexture("UI/Panel_Border_T.png"); };
		inline FTexture& panelCenter() { return getTexture("UI/Panel_Center.png"); };
		inline FTexture& panelCornerBL() { return getTexture("UI/Panel_Corner_BL.png"); };
		inline FTexture& panelCornerBR() { return getTexture("UI/Panel_Corner_BR.png"); };
		inline FTexture& panelCornerTL() { return getTexture("UI/Panel_Corner_TL.png"); };
		inline FTexture& panelCornerTR() { return getTexture("UI/Panel_Corner_TR.png"); };
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
		inline FTexture& smallPanelCornerBL() { return getTexture("UI/SmallPanel_Corner_BL.png"); };
		inline FTexture& smallPanelCornerBR() { return getTexture("UI/SmallPanel_Corner_BR.png"); };
		inline FTexture& smallPanelCornerTL() { return getTexture("UI/SmallPanel_Corner_TL.png"); };
		inline FTexture& smallPanelCornerTR() { return getTexture("UI/SmallPanel_Corner_TR.png"); };
		inline FTexture& squareButton() { return getTexture("UI/SquareButton.png"); };
	private:
		uptr<Cache<BorderedDrawable>> panelCache;
		uptr<Cache<VerticalDrawable>> scrollbarCache;
		uptr<Cache<VerticalDrawable>> scrollbuttonCache;
		uptr<Cache<BorderedDrawable>> smallPanelCache;
	};
}