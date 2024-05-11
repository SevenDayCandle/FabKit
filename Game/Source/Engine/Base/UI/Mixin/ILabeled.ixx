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

		ILabeled& withLabel(FFont& font, str text, float x = 0, float y = cfg.renderScale(-36), sdl::Color color = sdl::COLOR_WHITE, sdl::Color colorOutline = sdl::COLOR_BLACK);

	protected:
		ILabeled() {}
	};

	ILabeled& ILabeled::withLabel(FFont& font, str text, float x, float y, sdl::Color color, sdl::Color colorOutline)
	{
		label = std::make_unique<TextInfo>(font, text, color, colorOutline);
		label->setPos(x, y);
		return *this;
	}
}