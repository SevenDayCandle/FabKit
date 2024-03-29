export module fbc.hitbox;

import fbc.futil;
import sdl;

export namespace fbc {
	export class Hitbox : public sdl::RectF {
	public:
		Hitbox(): sdl::RectF() {}
		Hitbox(float offsetWidth, float offsetHeight) : sdl::RectF(), offsetWidth(offsetWidth), offsetHeight(offsetHeight) {}
		Hitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight) : sdl::RectF(), offsetX(offsetX), offsetY(offsetY), offsetWidth(offsetWidth), offsetHeight(offsetHeight) {}
		virtual ~Hitbox() {}

		inline bool isClicked() { return hovered && sdl::mouseIsLeftClicked(); };
		inline bool isClickedRight() { return hovered && sdl::mouseIsRightClicked(); };
		inline bool isHovered() const { return hovered; }
		inline bool isJust() const { return just; }
		inline bool justClicked() { return hovered && sdl::mouseIsLeftJustClicked(); };
		inline bool justClickedRight() { return hovered && sdl::mouseIsRightJustClicked(); };
		inline bool justHovered() const { return hovered && just; }
		inline float cX() { return x + (w / 2); }
		inline float cY() { return y + (h / 2); }
		inline float getOffsetX() { return offsetX; }
		inline float getOffsetY() { return offsetY; }
		inline Hitbox& moveCenter(const float x, const float y) { return move(x - (w / 2), y - (h / 2)); }
		Hitbox& setOffsetPos(const float x, const float y);
		Hitbox& setOffsetSize(const float x, const float y);
		Hitbox& setOffsetX(const float x);
		Hitbox& setOffsetY(const float y);
		Hitbox& setOffsetWidth(const float x);
		Hitbox& setOffsetHeight(const float y);
		virtual Hitbox& move(const float x, const float y);
		virtual Hitbox& resize(const float x, const float y);
		virtual void update();

		virtual void refreshPosition() = 0;
		virtual void refreshSize() = 0;
	protected:
		bool just = false;
		bool hovered = false;
		float offsetX;
		float offsetY;
		float offsetWidth;
		float offsetHeight;

		virtual bool isMouseInHoverRange();
	};

	// Return true if the mouse is within the rectangle. Note that the Y coordinates goes from top to bottom, with 0,0 being the top-left corner of the screen
	bool Hitbox::isMouseInHoverRange() {
		int mx = sdl::mouseGetX();
		int my = sdl::mouseGetY();
		return mx >= x && my >= y && mx < x + w && my < y + h;
	}

	// Move the bottom-left corner of the ui
	Hitbox& Hitbox::move(const float x, const float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	// Resize the ui
	Hitbox& Hitbox::resize(const float x, const float y)
	{
		this->w = x;
		this->h = y;
		return *this;
	}

	// Change the x/y offset ratio
	Hitbox& Hitbox::setOffsetPos(const float x, const float y)
	{
		offsetX = x;
		offsetY = y;
		refreshPosition();
		return *this;
	}

	// Change the width/height offset ratio
	Hitbox& Hitbox::setOffsetSize(const float x, const float y)
	{
		offsetWidth = x;
		offsetHeight = y;
		refreshSize();
		return *this;
	}

	// Change the x offset ratio
	Hitbox& Hitbox::setOffsetX(const float x)
	{
		offsetX = x;
		refreshPosition();
		return *this;
	}

	// Change the y offset ratio
	Hitbox& Hitbox::setOffsetY(const float y)
	{
		offsetY = y;
		refreshPosition();
		return *this;
	}

	// Change the width offset ratio
	Hitbox& Hitbox::setOffsetWidth(const float x)
	{
		offsetWidth = x;
		refreshSize();
		return *this;
	}

	// Change the height offset ratio
	Hitbox& Hitbox::setOffsetHeight(const float y)
	{
		offsetHeight = y;
		refreshSize();
		return *this;
	}

	// State update
	void Hitbox::update() {
		if (just) { just = false; }
		if (!hovered) {
			hovered = isMouseInHoverRange();
			if (hovered) {
				just = true;
			}
		}
		else {
			hovered = isMouseInHoverRange();
		}
	}
}