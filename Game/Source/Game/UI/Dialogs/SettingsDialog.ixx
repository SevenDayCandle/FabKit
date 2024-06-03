export module fbc.SettingsDialog;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.UIDialog;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.ScreenManager;
import fbc.ScreenSizeHitbox;
import fbc.SettingsDialogPage;
import fbc.UINavigation;
import fbc.UIButton;
import fbc.UITextButton;
import sdl;
import std;

export namespace fbc {
	export class SettingsDialog : public UIDialog {
	public:
		SettingsDialog(): UIDialog(new ScreenSizeHitbox(0.25, 0.25, 0.5, 0.5), cct.images.panel) {
			graphics.addDropdown<pair<int,int>, ilist<pair<int,int>>>(cfg.graphicsResolution, cct.strings.options_graphics_resolution(), RESOLUTIONS, [](const pair<int,int>& item) { return futil::dimensionString(item); });
			graphics.addToggle(cfg.graphicsVSync, cct.strings.options_graphics_vsync());

			ilist<SettingsDialogPage*> items = { &graphics, &sound, &text };
			navigation.addItems(items);
			navigation.setOnChange([this](const SettingsDialogPage* chosen) {this->selected = const_cast<SettingsDialogPage*>(chosen); });
			selected = &graphics;

			UIButton& cancel = this->addElement(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 0, hb->getScaleOffsetSizeY() * 0.9f, 300, 100),
				cct.images.thickPanel,
				cct.fontRegular(),
				cct.strings.ui_cancel())
			).setOnClick([this](UIButton& b) {screenManager::closeOverlay(this);});
			UIButton& apply = this->stackElementXDir(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 300, 100),
				cct.images.thickPanel,
				cct.fontRegular(),
				cct.strings.ui_apply())
			).setOnClick([this](UIButton& b) { applyAll(); });
			UIButton& save = this->stackElementXDir(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb,300, 100),
				cct.images.thickPanel,
				cct.fontRegular(),
				cct.strings.ui_save())
			).setOnClick([this](UIButton& b) {
					applyAll();
					screenManager::closeOverlay(this);
				});
		}
		virtual ~SettingsDialog() {}

		UINavigation<SettingsDialogPage>& navigation = this->addElement(std::make_unique<UINavigation<SettingsDialogPage>>(new RelativeHitbox(*hb, -330, 0, 300, 100)));
		SettingsDialogPage graphics = page(cct.strings.options_section_graphics());
		SettingsDialogPage sound = page(cct.strings.options_section_sound());
		SettingsDialogPage text = page(cct.strings.options_section_text());

		virtual bool isHovered() override;
		void renderImpl() override;
		void updateImpl() override;

		inline static void openNew() { screenManager::openOverlay(std::make_unique<SettingsDialog>()); } // Displays a new Settings Dialog
	protected:
		inline SettingsDialogPage page(strv name) { return SettingsDialogPage(new RelativeHitbox(*hb, hb->w * 0.1f, hb->h * 0.1f, hb->w * 0.8f, hb->h * 0.7f), name); }

		void applyAll();
		void resetCurrent();
	private:
		SettingsDialogPage* selected;
	};

	// The navigation lies outside of the dialog box
	bool SettingsDialog::isHovered()
	{
		return UIDialog::isHovered() || navigation.isHovered();
	}

	void SettingsDialog::renderImpl()
	{
		UIDialog::renderImpl();
		if (selected) {
			selected->renderImpl();
		}
	}

	void SettingsDialog::updateImpl()
	{
		UIDialog::updateImpl();
		if (selected) {
			selected->updateImpl();
		}
	}

	void SettingsDialog::applyAll()
	{
		for (SettingsDialogPage* page : navigation.getAllItems()) {
			page->commit();
		}
	}
}