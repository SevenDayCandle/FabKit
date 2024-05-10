export module fbc.ILabeled;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.TextInfo;
import sdl;
import std;

export namespace fbc {
	export class ILabeled {
	public:
		virtual ~ILabeled() {}

		ILabeled& withLabel(FFont& font, str text, sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK);

		uptr<TextInfo> label;
	protected:
		ILabeled() {}
	};

	ILabeled& ILabeled::withLabel(FFont& font, str text, sdl::Color color, sdl::Color colorOutline)
	{
		return *this;
	}
}