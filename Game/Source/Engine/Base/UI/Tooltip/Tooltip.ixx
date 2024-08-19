export module fbc.Tooltip;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FWindow;
import fbc.FUtil;
import fbc.GenericTip;
import fbc.UIBase;
import fbc.IDrawable;
import fbc.TextDrawable;
import sdl;
import std;

namespace fbc {
	export constexpr float PADDING = 24;

	export class Tooltip : public TextDrawable, public GenericTip {
	public:
		Tooltip(FWindow& window, strv text, FFont& font = cct.fontSmall(), float boxSize = DEFAULT_SIZE, IDrawable& background = cct.images.uiDarkPanelRound) : TextDrawable(font, text), GenericTip(window, boxSize), background(background) {}
		virtual ~Tooltip() override = default;

		inline virtual void update() override {}

		virtual void open() override;
		virtual void refreshDimensions() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
	protected:
		IDrawable& background;

		inline virtual int getLimitWidth() override { return bounds.w - cfg.renderScale(PADDING * 2); }

		virtual void updateBounds() override;
		void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline) override;
	};

	// When queued for rendering, create the text and bounding box if they don't exist
	void Tooltip::open()
	{
		if (!TextDrawable::hasCache()) {
			updateCache(this->text, this->color, this->colorOutline);
		}
	}

	void Tooltip::refreshDimensions()
	{
		TextDrawable::refreshCache();
	}

	void Tooltip::render(sdl::SDLBatchRenderPass& rp)
	{
		background.draw(rp, bounds, win.getW(), win.getH());
		TextDrawable::drawText(rp, bounds.x, bounds.y, win.getW(), win.getH());
	}

	// Stretch the box background to fit the words in the tooltip
	void Tooltip::updateBounds()
	{
		float off = cfg.renderScale(PADDING);
		TextDrawable::setPos(off, off);
		bounds.h = TextDrawable::getTextHeight() + off * 2;
	}

	void Tooltip::updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline)
	{
		TextDrawable::updateCache(text, color, colorOutline);
		updateBounds();
	}
}