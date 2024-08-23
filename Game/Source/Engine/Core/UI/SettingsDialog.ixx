export module fbc.SettingsDialog;

import fbc.CoreConfig;
import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.ScreenSizeHitbox;
import fbc.SettingsDialogPage;
import fbc.UIButton;
import fbc.UIDialog;
import fbc.UIEntry;
import fbc.UINavigation;
import fbc.UITextButton;
import fbc.WindowMode;
import std;

namespace fbc {
	export class SettingsDialog : public UIDialog {
	public:
		SettingsDialog(FWindow& window): UIDialog(window, make_unique<ScreenSizeHitbox>(window, 0.25, 0.25, 0.5, 0.5), window.cct.images.uiDarkPanelRound) {
			graphics.addDropdown<pair<int,int>, ilist<pair<int,int>>>(win.cfg.graphicsResolution, win.cct.strings.options_graphics_resolution(), RESOLUTIONS, [](const pair<int,int>& item) { return futil::dimensionString(item); });
			graphics.addDropdown<WindowMode, ilist<WindowMode>>(win.cfg.graphicsWindowMode, win.cct.strings.options_graphics_window_mode(), WINDOWMODE_ALL, [this](const WindowMode& item) { return str(windowScreenName(item)); });
			graphics.addSlider(win.cfg.graphicsFPS, win.cct.strings.options_graphics_fps());
			graphics.addToggle(win.cfg.graphicsVSync, win.cct.strings.options_graphics_vsync());

			sound.addSlider(win.cfg.soundVolumeMaster, win.cct.strings.options_sound_master(), 300);
			sound.addSlider(win.cfg.soundVolumeEffects, win.cct.strings.options_sound_effects(), 300);
			sound.addSlider(win.cfg.soundVolumeMusic, win.cct.strings.options_sound_music(), 300);

			navigation.addItems(&graphics, &sound, &text);

			UIButton& cancel = this->add(std::make_unique<UITextButton>(win,
				relhb(0, hb->getScaleOffSizeY() * 0.88f, 300, 100),
				win.cct.images.uiPanelRound,
				win.cct.fontRegular(),
				win.cct.strings.ui_cancel())
			).setOnClick([this](UIButton& b) {this->win.closeOverlay(this);});
			UIButton& apply = this->stackXDir(std::make_unique<UITextButton>(win,
				relhb(300, 100),
				win.cct.images.uiPanelRound,
				win.cct.fontRegular(),
				win.cct.strings.ui_apply())
			).setOnClick([this](UIButton& b) { applyAll(); });
			UIButton& save = this->stackXDir(std::make_unique<UITextButton>(win,
				relhb(300, 100),
				win.cct.images.uiPanelRound,
				win.cct.fontRegular(),
				win.cct.strings.ui_save())
			).setOnClick([this](UIButton& b) {
					applyAll();
					this->win.closeOverlay(this);
				});
		}

		UINavigation<SettingsDialogPage>& navigation = this->add(std::make_unique<UINavigation<SettingsDialogPage>>(win, relhb(-330, 0, 300, 100)));
		SettingsDialogPage graphics = page(win.cct.strings.options_section_graphics());
		SettingsDialogPage sound = page(win.cct.strings.options_section_sound());
		SettingsDialogPage text = page(win.cct.strings.options_section_text());
		SettingsDialogPage hotkeys = page(win.cct.strings.options_section_graphics());

		virtual bool isHovered() override;
		strv windowScreenName(WindowMode mode);

		inline static void openNew(FWindow& window) { window.openOverlay(std::make_unique<SettingsDialog>(window)); } // Displays a new Settings Dialog
	protected:
		inline SettingsDialogPage page(strv name) { return SettingsDialogPage(win, relhb(hb->w * 0.1f, hb->h * 0.1f, hb->w * 0.8f, hb->h * 0.7f), name); }

		void applyAll();
		void resetCurrent();
	};

	bool SettingsDialog::isHovered()
	{
		return UIDialog::isHovered() || navigation.isHovered();
	}

	void SettingsDialog::applyAll()
	{
		for (const UIEntry<SettingsDialogPage>& page : navigation) {
			SettingsDialogPage& item = const_cast<SettingsDialogPage&>(page.item);
			item.commit();
		}

		win.cfg.commit();
	}

	void SettingsDialog::resetCurrent()
	{
		SettingsDialogPage* selected = navigation.getSelectedItem();
		if (selected) {
			selected->reset();
		}
	}

	strv SettingsDialog::windowScreenName(WindowMode mode)
	{
		switch (mode) {
		case BORDERLESS_FULLSCREEN:
			return win.cct.strings.options_graphics_window_mode_borderless();
		case FULLSCREEN:
			return win.cct.strings.options_graphics_window_mode_fullscreen();
		default:
			return win.cct.strings.options_graphics_window_mode_windowed();
		}
	}
}