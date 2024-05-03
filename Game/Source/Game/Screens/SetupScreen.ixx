export module fbc.setupScreen;

import fbc.coreContent;
import fbc.futil;
import fbc.language;
import fbc.relativeHitbox;
import fbc.scaleHitbox;
import fbc.screenSizeHitbox;
import fbc.screenManager;
import fbc.uiButton;
import fbc.uiSearchableDropdown;
import fbc.uiEntry;
import fbc.uiMenu;
import fbc.uiTextButton;
import fbc.uiToggle;
import fbc.uiVerticalCanvas;
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

			vec<ref<Language>> langs = Language::all();
			UISearchableDropdown<ref<Language>>& dr = addElement(UISearchableDropdown<ref<Language>>::multiMenu(new RelativeHitbox(*hb, 390, 1100, 400, 100)));
			dr.setItems(langs);
		}
	};
}