export module fbc.Tooltip;

import fbc.CoreConfig;
import fbc.CoreContent;
import fbc.FFont;
import fbc.FUtil;
import fbc.ScreenManager;
import fbc.UIBase;
import fbc.IDrawable;
import fbc.IOverlay;
import fbc.TextInfo;
import sdl;
import std;

namespace fbc {
	export constexpr float DEFAULT_SIZE = 100;
	export constexpr float PADDING = 24;
	export constexpr float QUEUE_OFFSET_X = 36;
	export constexpr float QUEUE_OFFSET_Y = 18;

	export class Tooltip : public TextInfo, public IOverlay {
	public:
		Tooltip(strv text, FFont& font = cct.fontSmall(), float boxSize = DEFAULT_SIZE, IDrawable& background = cct.images.darkPanelRound) : TextInfo(font, text), bounds(0, 0, boxSize, 0), background(background) {
			updateBounds();
		}

		inline virtual void update() override {}

		Tooltip& setBoxSize(float boxSize);
		virtual void open() override;
		virtual void queue(float x = sdl::mouseGetX() + cfg.renderScale(QUEUE_OFFSET_X), float y = sdl::mouseGetY() + cfg.renderScale(QUEUE_OFFSET_Y));
		virtual void render() override;
	protected:
		IDrawable& background;
		sdl::RectF bounds;

		inline virtual int getLimitWidth() override { return bounds.w - cfg.renderScale(PADDING * 2); }

		virtual void updateBounds();
		void updateCache(strv text, const sdl::Color& color, const sdl::Color& colorOutline) override;
	};

	// When queued for rendering, create the text and bounding box if they don't exist
	void Tooltip::open()
	{
		if (!TextInfo::hasCache()) {
			updateCache(this->text, this->color, this->colorOutline);
		}
	}

	// Queue this tooltip for rendering at a specific position
	void Tooltip::queue(float x, float y)
	{
		float xBound = cfg.getScreenXSize();
		float yBound = cfg.getScreenYSize();
		bounds.x = x + bounds.w >= xBound ? xBound - bounds.w : x;
		bounds.y = y + bounds.h >= xBound ? xBound - bounds.h : y;
		screenManager::queueTip(this);
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