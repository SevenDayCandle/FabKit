export module fbc.CoreAudio;

import fbc.BaseContent;
import fbc.FUtil;
import fbc.StaticLoadables;
import fbc.FSound;
import sdl;
import std;

export namespace fbc {
	export class CoreAudio : public StaticLoadables {
	public:
		CoreAudio(BaseContent& cnt) : StaticLoadables(cnt) {}

		FSound& uiClick = cacheSound("UI/Click1.wav");
		FSound& uiHover = cacheSound("UI/Hover1.wav");
	};
}