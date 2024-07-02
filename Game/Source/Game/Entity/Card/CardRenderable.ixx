export module fbc.CardRenderable;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.UIBase;
import sdl;
import std;

namespace fbc {
	export class CardRenderable : public UIBase {
	public:
		CardRenderable(Hitbox* hb): UIBase(hb) {}
	};
}