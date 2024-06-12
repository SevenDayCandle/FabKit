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
import fbc.WindowMode;
import sdl;
import std;

export namespace fbc {
	export class SettingsDialog : public UIDialog {
	public:
		SettingsDialog(): UIDialog(new ScreenSizeHitbox(0.25, 0.25, 0.5, 0.5), cct.images.darkPanelRound) {
			graphics.addDropdown<pair<int,int>, ilist<pair<int,int>>>(cfg.graphicsResolution, cct.strings.options_graphics_resolution(), RESOLUTIONS, [](const pair<int,int>& item) { return futil::dimensionString(item); });
			graphics.addDropdown<WindowMode, ilist<WindowMode>>(cfg.graphicsWindowMode, cct.strings.options_graphics_window_mode(), WINDOWMODE_ALL, [](const WindowMode& item) { return windowScreenName(item); });
			graphics.addToggle(cfg.graphicsVSync, cct.strings.options_graphics_vsync());

			sound.addSlider(cfg.soundVolumeMaster, cct.strings.options_sound_master(), 300);
			sound.addSlider(cfg.soundVolumeEffects, cct.strings.options_sound_effects(), 300);
			sound.addSlider(cfg.soundVolumeMusic, cct.strings.options_sound_music(), 300);

			navigation.addItems(&graphics, &sound, &text);

			UIButton& cancel = this->addElement(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 20, hb->getScaleOffsetSizeY() * 0.88f, 300, 100),
				cct.images.panelRound,
				cct.fontRegular(),
				cct.strings.ui_cancel())
			).setOnClick([this](UIButton& b) {screenManager::closeOverlay(this);});
			UIButton& apply = this->stackElementXDir(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 300, 100),
				cct.images.panelRound,
				cct.fontRegular(),
				cct.strings.ui_apply())
			).setOnClick([this](UIButton& b) { applyAll(); });
			UIButton& save = this->stackElementXDir(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb,300, 100),
				cct.images.panelRound,
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

		inline static void openNew() { screenManager::openOverlay(std::make_unique<SettingsDialog>()); } // Displays a new Settings Dialog

		static str windowScreenName(WindowMode mode);
	protected:
		inline SettingsDialogPage page(strv name) { return SettingsDialogPage(new RelativeHitbox(*hb, hb->w * 0.1f, hb->h * 0.1f, hb->w * 0.8f, hb->h * 0.7f), name); }

		void applyAll();
		void resetCurrent();
	};

	bool SettingsDialog::isHovered()
	{
		return UIDialog::isHovered() || navigation.isHovered();
	}

	void SettingsDialog::applyAll()
	{
		for (const SettingsDialogPage* page : navigation.getAllItems()) {
			const_cast<SettingsDialogPage*>(page)->commit();
		}
		cfg.commit();
	}

	void SettingsDialog::resetCurrent()
	{
		SettingsDialogPage* selected = navigation.getSelectedItem();
		if (selected) {
			selected->reset();
		}
	}

	/* Statics */

	str SettingsDialog::windowScreenName(WindowMode mode)
	{
		switch (mode) {
		case BORDERLESS_FULLSCREEN:
			return cct.strings.options_graphics_window_mode_borderless();
		case FULLSCREEN:
			return cct.strings.options_graphics_window_mode_fullscreen();
		default:
			return cct.strings.options_graphics_window_mode_windowed();
		}
	}
}