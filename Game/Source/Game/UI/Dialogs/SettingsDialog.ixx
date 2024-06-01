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
import sdl;
import std;

export namespace fbc {
	export class SettingsDialog : public UIDialog {
	public:
		SettingsDialog(): UIDialog(new ScreenSizeHitbox(0.25, 0.25, 0.5, 0.5), cct.images.largePanel) {
			graphics.addDropdown<pair<int,int>, ilist<pair<int,int>>>(cfg.graphicsResolution, cct.strings.options_graphics_resolution(), RESOLUTIONS, [](const pair<int,int>& item) { return futil::dimensionString(item); });
			graphics.addToggle(cfg.graphicsVSync, cct.strings.options_graphics_vsync());

			ilist<SettingsDialogPage*> items = { &graphics, &sound, &text };
			navigation.addItems(items);
			navigation.setOnChange([this](const SettingsDialogPage* chosen) {this->selected = const_cast<SettingsDialogPage*>(chosen); });
			selected = &graphics;
		}
		virtual ~SettingsDialog() {}

		UINavigation<SettingsDialogPage> navigation = UINavigation<SettingsDialogPage>(new RelativeHitbox(*hb, -330, 0, 300, 100));
		SettingsDialogPage graphics = page(cct.strings.options_section_graphics());
		SettingsDialogPage sound = page(cct.strings.options_section_sound());
		SettingsDialogPage text = page(cct.strings.options_section_text());

		virtual bool isHovered() override;
		void renderImpl() override;
		void updateImpl() override;

		inline static void openNew() { screenManager::openOverlay(std::make_unique<SettingsDialog>()); } // Displays a new Settings Dialog
	protected:
		inline SettingsDialogPage page(strv name) { return SettingsDialogPage(new RelativeHitbox(*hb, hb->w * 0.05f, hb->h * 0.05f, hb->w * 0.9f, hb->h * 0.7f), name); }
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
		navigation.renderImpl();
		if (selected) {
			selected->renderImpl();
		}
	}

	void SettingsDialog::updateImpl()
	{
		UIDialog::updateImpl();
		navigation.updateImpl();
		if (selected) {
			selected->updateImpl();
		}
	}
}