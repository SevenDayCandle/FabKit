export module fab.Tooltip;

import fab.FFont;
import fab.FWindow;
import fab.FUtil;
import fab.GenericTip;
import fab.IDrawable;
import fab.TextDrawable;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import std;

namespace fab {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float PADDING = 24;

	export class Tooltip : public GenericTip {
	public:
		Tooltip(FWindow& window, strv text, FFont& font, float wOff, IDrawable& background) : GenericTip(window), background(background), wOff(wOff), text(font, text, getLimitWidth(wOff)) {}
		Tooltip(FWindow& window, strv text) : Tooltip(window, text, window.props.fontSmall(), DEFAULT_SIZE, window.props.defaultBackground()) {}

		virtual ~Tooltip() override = default;

		inline virtual float getHeight() const override { return h; }
		inline virtual float getWidth() const override { return w; }
		inline virtual void update() override {}

		virtual void open() override;
		virtual void refreshDimensions() override;
		virtual void render(BatchRenderPass& rp) override;
	protected:
		float h;
		float w;
		float wOff;
		IDrawable& background;
		TextDrawable text;

		inline int getLimitWidth(int w) const { return w - win.renderScale(PADDING * 2); }

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

	void Tooltip::render(BatchRenderPass& rp)
	{
		float off = win.renderScale(PADDING);
		background.draw(rp, x, y, w, h);
		text.drawFull(rp, x + off, y + off);
	}

	// Stretch the box background to fit the words in the tooltip
	void Tooltip::updateBounds()
	{
		w = win.renderScale(wOff);
		h = text.getHeight() + win.renderScale(PADDING) * 2;
	}
}