export module fbc.SettingsDialog;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.UIDialog;
import fbc.FUtil;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import fbc.ScreenSizeHitbox;
import fbc.SettingsDialogPage;
import fbc.UINavigation;
import sdl;
import std;

export namespace fbc {
	export class SettingsDialog : public UIDialog {
	public:
		SettingsDialog(): UIDialog(new ScreenSizeHitbox(0.5, 0.5), cct.images.largePanel) {

			ilist<SettingsDialogPage*> items = { &graphics, &sound, &text };
			navigation.addItems(items);
		}
		virtual ~SettingsDialog() {}

		UINavigation<SettingsDialogPage> navigation = UINavigation<SettingsDialogPage>(new RelativeHitbox(*hb, -330, 0, 300, 100));
		SettingsDialogPage graphics = page(cct.strings.options_section_graphics());
		SettingsDialogPage sound = page(cct.strings.options_section_sound());
		SettingsDialogPage text = page(cct.strings.options_section_text());

		void renderImpl() override;
		void updateImpl() override;
	protected:
		inline SettingsDialogPage page(strv name) { return SettingsDialogPage(new RelativeHitbox(*hb), name); }
	};

}