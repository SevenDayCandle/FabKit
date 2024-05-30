export module fbc.SetupScreen;

import fbc.CoreContent;
import fbc.FUtil;
import fbc.Language;
import fbc.RelativeHitbox;
import fbc.ScaleHitbox;
import fbc.ScreenSizeHitbox;
import fbc.ScreenManager;
import fbc.UIButton;
import fbc.UIGrid;
import fbc.UISearchableDropdown;
import fbc.UISlider;
import fbc.UIEntry;
import fbc.UIMenu;
import fbc.UINumberInput;
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
				new RelativeHitbox(*hb, 490, 200, 170, 150),
				cct.strings.ui_close()));
			b.setOnClick([](UIButton& i) {
				screenManager::closeCurrentScreen();
			});

			UIToggle& f = stackElementXDir(std::make_unique<UIToggle>(
				new RelativeHitbox(*hb, 100, 100),
				cct.strings.ui_confirm()
				));

			UISearchableDropdown<Language>& dr = stackElementXDir(UISearchableDropdown<Language>::multiMenu(new RelativeHitbox(*hb, 400, 100)));
			dr.setItems(Language::all());

			UITextInput& inp = stackElementYDir(std::make_unique<UITextInput>(new RelativeHitbox(*hb, 500, 1400, 500, 100)));

			UIGrid<UITextButton>& buttonGrid = stackElementYDir(std::make_unique<UIGrid<UITextButton>>(new RelativeHitbox(*hb,300, 300)));
			buttonGrid.addItem(std::make_unique<UITextButton>(new RelativeHitbox(*hb,100, 100), "A"));
			buttonGrid.addItem(std::make_unique<UITextButton>(new RelativeHitbox(*hb, 100, 100), "B"));
			buttonGrid.addItem(std::make_unique<UITextButton>(new RelativeHitbox(*hb, 100, 100), "C"));
			buttonGrid.addItem(std::make_unique<UITextButton>(new RelativeHitbox(*hb, 100, 100), "D"));

			UINumberInput& ee = stackElementYDir(std::make_unique<UINumberInput>(new RelativeHitbox(*hb,400, 100)));

			UISlider& ree = stackElementYDir(std::make_unique<UISlider>(new RelativeHitbox(*hb, 200, 100)), 300);
			ree.withLabel("Test");
		}
	};
}