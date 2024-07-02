export module fbc.TitleTooltip;

import fbc.CoreContent;
import fbc.FFont;
import fbc.IDrawable;
import fbc.FUtil;
import fbc.Tooltip;
import sdl;
import std;

namespace fbc {
	export class TitleTooltip : public Tooltip {
	public:
		TitleTooltip(strv title, strv text, FFont& titleFont = cct.fontRegular(), FFont& font = cct.fontSmall(), float boxSize = DEFAULT_SIZE, IDrawable& background = cct.images.darkPanelRound): Tooltip(text, font, boxSize, background), title(titleFont, title) {}

		TitleTooltip& setTitle(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		virtual void render() override;
	protected:
		TextInfo title;

		virtual void updateBounds() override;
	};
}