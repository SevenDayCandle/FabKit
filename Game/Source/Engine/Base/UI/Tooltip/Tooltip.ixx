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
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float PADDING = 24;

	export class Tooltip : public GenericTip {
	public:
		Tooltip(FWindow& window, strv text, FFont& font = cct.fontSmall(), float wOff = DEFAULT_SIZE, IDrawable& background = cct.images.uiDarkPanelRound) : GenericTip(window), background(background), wOff(wOff), text(font, text, getLimitWidth(wOff)) {}
		virtual ~Tooltip() override = default;

		inline virtual float getHeight() const override { return h; }
		inline virtual float getWidth() const override { return w; }
		inline virtual void update() override {}

		virtual void open() override;
		virtual void refreshDimensions() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) override;
	protected:
		float h;
		float w;
		float wOff;
		IDrawable& background;
		TextDrawable text;

		inline static int getLimitWidth(int w) { return w - cfg.renderScale(PADDING * 2); }

		virtual void updateBounds() override;
	};

	// When queued for rendering, create the text and bounding box if they don't exist
	void Tooltip::open()
	{
		if (!text.loaded()) {
			text.reload();
			updateBounds();
		}
	}

	void Tooltip::refreshDimensions()
	{
		text.setWidth(getLimitWidth(wOff));
		updateBounds();
	}

	void Tooltip::render(sdl::SDLBatchRenderPass& rp)
	{
		background.draw(rp, x, y, w, h, win.getW(), win.getH());
		text.draw(rp, x, y, win.getW(), win.getH());
	}

	// Stretch the box background to fit the words in the tooltip
	void Tooltip::updateBounds()
	{
		float off = cfg.renderScale(PADDING);
		text.setPos(off, off);
		w = cfg.renderScale(wOff);
		h = text.getHeight() + off * 2;
	}
}