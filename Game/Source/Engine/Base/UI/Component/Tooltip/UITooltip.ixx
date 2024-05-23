export module fbc.UITooltip;

import fbc.FUtil;
import fbc.TextInfo;
import std;

export namespace fbc {
	export class UITooltip : public TextInfo {
	public:

		str ID;

		virtual void dispose();
		virtual void render();
		virtual void update();
	};
}