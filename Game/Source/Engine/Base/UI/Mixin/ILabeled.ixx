export module fbc.ILabeled;

import fbc.CoreContent;
import fbc.CoreConfig;
import fbc.FFont;
import fbc.FUtil;
import fbc.TextInfo;
import sdl;
import std;

export namespace fbc {
	export struct ILabeled {
	public:
		virtual ~ILabeled() {}

		uptr<TextInfo> label;

		inline strv getLabelText() const { return label ? label->getText() : ""; }

		ILabeled& withLabel(str text, FFont& font = cct.fontBold(), float x = 0, float y = cfg.renderScale(-80), sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK);

	protected:
		ILabeled() {}
	};

	ILabeled& ILabeled::withLabel(str text, FFont& font, float x, float y, sdl::Color color, sdl::Color colorOutline)
	{
		label = std::make_unique<TextInfo>(font, text, color, colorOutline);
		label->setPos(x, y);
		return *this;
	}
}