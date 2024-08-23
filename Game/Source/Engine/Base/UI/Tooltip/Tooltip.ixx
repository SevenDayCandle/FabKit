export module fbc.Tooltip;

import fbc.FFont;
import fbc.FWindow;
import fbc.FUtil;
import fbc.GenericTip;
import fbc.IDrawable;
import fbc.TextDrawable;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import std;

namespace fbc {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float PADDING = 24;

	export class Tooltip : public GenericTip {
	public:
		Tooltip(FWindow& window, strv text, FFont& font, float wOff, IDrawable& background) : GenericTip(window), background(background), wOff(wOff), text(font, text, getLimitWidth(wOff)) {}
		Tooltip(FWindow& window, strv text) : Tooltip(window, text, window.cct.fontSmall(), DEFAULT_SIZE, window.cct.images.uiDarkPanelRound) {}

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

		inline int getLimitWidth(int w) const { return w - win.cfg.renderScale(PADDING * 2); }

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
		float off = win.cfg.renderScale(PADDING);
		text.setPos(off, off);
		w = win.cfg.renderScale(wOff);
		h = text.getHeight() + off * 2;
	}
}