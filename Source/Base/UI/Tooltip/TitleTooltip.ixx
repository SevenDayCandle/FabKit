export module fab.TitleTooltip;

import fab.FFont;
import fab.FUtil;
import fab.FWindow;
import fab.IDrawable;
import fab.TextDrawable;
import fab.Tooltip;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import std;

namespace fab {
	export class TitleTooltip : public Tooltip {
	public:
		TitleTooltip(FWindow& window, strv title, strv text, FFont& titleFont, FFont& font, float boxSize, IDrawable& background) :
			Tooltip(window, text, font, boxSize, background), title(titleFont, title) {}
		TitleTooltip(FWindow& window, strv title, strv text) :
			TitleTooltip(window, title, text, window.props.fontRegular(), window.props.fontSmall(), DEFAULT_SIZE, window.props.defaultBackground()) {}


		TitleTooltip& setTitle(strv text, sdl::Color color, sdl::Color colorOutline, const FFont& font);
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
	protected:
		TextDrawable title;

		virtual void updateBounds() override;
	};
}