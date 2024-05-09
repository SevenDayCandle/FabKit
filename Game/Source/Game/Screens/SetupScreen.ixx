export module fbc.SetupScreen;

import fbc.CoreContent;
import fbc.futil;
import fbc.Language;
import fbc.RelativeHitbox;
import fbc.ScaleHitbox;
import fbc.ScreenSizeHitbox;
import fbc.screenManager;
import fbc.UIButton;
import fbc.UIGrid;
import fbc.UISearchableDropdown;
import fbc.UIEntry;
import fbc.UIMenu;
import fbc.UITextButton;
import fbc.UITextInput;
import fbc.UIToggle;
import fbc.UIVerticalCanvas;
import std;

export namespace fbc {
	export class SetupScreen : public UIVerticalCanvas {
	public:
		SetupScreen(): UIVerticalCanvas(new ScreenSizeHitbox()) {
			UITextButton& b = addElement(std::make_unique<UITextButton>(
				new RelativeHitbox(*hb, 190, 500, 170, 150),
				cct.images.smallPanel(),
				cct.fontRegular(),
				cct.strings.ui_close()));
			b.setOnClick([](UIButton& i) {
				screenManager::closeCurrentScreen();
			});

			UIToggle& f = addElement(std::make_unique<UIToggle>(
				new RelativeHitbox(*hb, 190, 800, 100, 100),
				cct.strings.ui_confirm(),
				cct.images.checkboxEmpty(),
				cct.images.checkboxFilled(),
				cct.fontRegular()
				));

			UISearchableDropdown<ref<Language>>& dr = addElement(UISearchableDropdown<ref<Language>>::multiMenu(new RelativeHitbox(*hb, 390, 1100, 400, 100)));
			dr.setItems(Language::all());

			UITextInput& inp = addElement(std::make_unique<UITextInput>(new RelativeHitbox(*hb, 500, 1400, 500, 100)));
		}
	};
}