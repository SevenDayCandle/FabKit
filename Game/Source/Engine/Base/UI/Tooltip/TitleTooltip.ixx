export module fbc.TitleTooltip;

import fbc.CoreContent;
import fbc.FFont;
import fbc.FWindow;
import fbc.IDrawable;
import fbc.FUtil;
import fbc.Tooltip;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class TitleTooltip : public Tooltip {
	public:
		TitleTooltip(FWindow& window, strv title, strv text, FFont& titleFont = cct.fontRegular(), FFont& font = cct.fontSmall(), float boxSize = DEFAULT_SIZE, IDrawable& background = cct.images.uiDarkPanelRound): Tooltip(window, text, font, boxSize, background), title(titleFont, title) {}

		TitleTooltip& setTitle(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
	protected:
		TextDrawable title;

		virtual void updateBounds() override;
	};
}