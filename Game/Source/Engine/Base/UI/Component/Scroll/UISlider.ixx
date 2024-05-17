export module fbc.UISlider;

import fbc.CoreContent;
import fbc.IDrawable;
import fbc.UIHorizontalScrollbar;
import fbc.UINumberInput;
import fbc.Hitbox;
import sdl;
import std;

export namespace fbc {
	export class UISlider : public UIHorizontalScrollbar {
	public:
		UISlider(Hitbox* hb, IDrawable& imageBar = cct.images.sliderEmpty, IDrawable& imageButton = cct.images.scrollbutton): UIHorizontalScrollbar(hb, imageBar, imageButton) {}
		virtual ~UISlider() {}
	};
}