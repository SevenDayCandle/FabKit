export module fbc.coreImages;

import fbc.baseContent;
import fbc.borderedDrawable;
import fbc.baseImages;
import fbc.cache;
import fbc.coreConfig;
import fbc.ftexture;
import fbc.futil;

export namespace fbc {
	export class CoreImages : public BaseImages {
	public:
		CoreImages(BaseContent& cnt) : BaseImages(cnt) {
			panelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(panelCenter(), panelBorderB(), panelBorderL(), panelBorderR(), panelBorderT(), panelCornerBL(), panelCornerBR(), panelCornerTL(), panelCornerTR()); });
			smallPanelCache = std::make_unique<Cache<BorderedDrawable>>([this]() { return BorderedDrawable(panelCenter(), smallPanelBorderB(), smallPanelBorderL(), smallPanelBorderR(), smallPanelBorderT(), smallPanelCornerBL(), smallPanelCornerBR(), smallPanelCornerTL(), smallPanelCornerTR()); });
		}

		inline BorderedDrawable& panel() { return *panelCache.get(); }
		inline BorderedDrawable& smallPanel() { return *smallPanelCache.get(); }

		inline FTexture& panelBorderB() { return getTexture("UI/Panel_Border_B.png"); };
		inline FTexture& panelBorderL() { return getTexture("UI/Panel_Border_L.png"); };
		inline FTexture& panelBorderR() { return getTexture("UI/Panel_Border_R.png"); };
		inline FTexture& panelBorderT() { return getTexture("UI/Panel_Border_T.png"); };
		inline FTexture& panelCenter() { return getTexture("UI/Panel_Center.png"); };
		inline FTexture& panelCornerBL() { return getTexture("UI/Panel_Corner_BL.png"); };
		inline FTexture& panelCornerBR() { return getTexture("UI/Panel_Corner_BR.png"); };
		inline FTexture& panelCornerTL() { return getTexture("UI/Panel_Corner_TL.png"); };
		inline FTexture& panelCornerTR() { return getTexture("UI/Panel_Corner_TR.png"); };
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
		uptr<Cache<BorderedDrawable>> smallPanelCache;
	};
}