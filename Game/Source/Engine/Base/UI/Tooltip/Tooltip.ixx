export module fbc.Tooltip;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.GenericTip;
import fbc.UIBase;
import fbc.IDrawable;
import fbc.TextInfo;
import sdl;
import std;

namespace fbc {
	export constexpr float PADDING = 24;

	export class Tooltip : public TextInfo, public GenericTip {
	public:
		Tooltip(strv text, FFont& font = cct.fontSmall(), float boxSize = DEFAULT_SIZE, IDrawable& background = cct.images.darkPanelRound) : TextInfo(font, text), GenericTip(boxSize), background(background) {}
		virtual ~Tooltip() override = default;

		inline virtual void update() override {}

		virtual void open() override;
		virtual void refreshDimensions() override;
		virtual void render() override;
	protected:
		IDrawable& background;

		inline virtual int getLimitWidth() override { return bounds.w - cfg.renderScale(PADDING * 2); }

		virtual void updateBounds() override;
		void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline) override;
	};

	// When queued for rendering, create the text and bounding box if they don't exist
	void Tooltip::open()
	{
		if (!TextInfo::hasCache()) {
			updateCache(this->text, this->color, this->colorOutline);
		}
	}

	void Tooltip::refreshDimensions()
	{
		TextInfo::refreshCache();
	}

	void Tooltip::render()
	{
		background.draw(&bounds);
		TextInfo::drawText(bounds.x, bounds.y);
	}

	// Stretch the box background to fit the words in the tooltip
	void Tooltip::updateBounds()
	{
		float off = cfg.renderScale(PADDING);
		TextInfo::setPos(off, off);
		bounds.h = TextInfo::getTextHeight() + off * 2;
	}

	void Tooltip::updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline)
	{
		TextInfo::updateCache(text, color, colorOutline);
		updateBounds();
	}
}