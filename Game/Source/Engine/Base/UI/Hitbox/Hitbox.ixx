export module fbc.Hitbox;

import fbc.FUtil;
import sdl;

export namespace fbc {
	export class Hitbox : public sdl::RectF {
	public:
		Hitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight) : sdl::RectF(0, 0, 0, 0), offsetPosX(offsetX), offsetPosY(offsetY), offsetSizeX(offsetWidth), offsetSizeY(offsetHeight) {}
		virtual ~Hitbox() {}

		inline bool isClicked() const { return hovered && sdl::mouseIsLeftClicked(); };
		inline bool isClickedRight() const { return hovered && sdl::mouseIsRightClicked(); };
		inline bool isHovered() const { return hovered; }
		inline bool isJust() const { return just; }
		inline bool justClicked() const { return hovered && sdl::mouseIsLeftJustClicked(); };
		inline bool justClickedRight() const { return hovered && sdl::mouseIsRightJustClicked(); };
		inline bool justHovered() const { return hovered && just; }
		inline bool justUnhovered() const { return !hovered && just; }
		inline float cX() const { return x + (w / 2); }
		inline float cY() const { return y + (h / 2); }
		inline float getOffsetPosX() const { return offsetPosX; }
		inline float getOffsetPosY() const { return offsetPosY; }
		inline float getOffsetSizeX() const { return offsetSizeX; }
		inline float getOffsetSizeY() const { return offsetSizeY; }
		inline Hitbox& moveCenter(const float x, const float y) { return move(x - (w / 2), y - (h / 2)); }

		Hitbox& setExactPos(const float x, const float y);
		Hitbox& setExactPosX(const float x);
		Hitbox& setExactPosY(const float y);
		Hitbox& setExactSize(const float x, const float y);
		Hitbox& setExactSizeX(const float x);
		Hitbox& setExactSizeY(const float y);
		Hitbox& setOffsetPos(const float x, const float y);
		Hitbox& setOffsetPosX(const float x);
		Hitbox& setOffsetPosY(const float y);
		Hitbox& setOffsetSize(const float x, const float y);
		Hitbox& setOffsetSizeX(const float x);
		Hitbox& setOffsetSizeY(const float y);
		void refresh();
		virtual Hitbox& move(const float x, const float y);
		virtual Hitbox& resize(const float x, const float y);
		virtual void update();
	protected:
		bool just = false;
		bool hovered = false;
		float offsetPosX = 0;
		float offsetPosY = 0;
		float offsetSizeX = 0;
		float offsetSizeY = 0;

		virtual bool isMouseHovering();

		virtual void refreshExactPosX() = 0;
		virtual void refreshExactPosY() = 0;
		virtual void refreshExactSizeX() = 0;
		virtual void refreshExactSizeY() = 0;
		virtual void refreshOffsetPosX() = 0;
		virtual void refreshOffsetPosY() = 0;
		virtual void refreshOffsetSizeX() = 0;
		virtual void refreshOffsetSizeY() = 0;
	};

	// Return true if the mouse is within the rectangle. Note that the Y coordinates goes from top to bottom, with 0,0 being the top-left corner of the screen
	bool Hitbox::isMouseHovering() {
		return sdl::mouseIsHovering(*this);
	}

	// Move the top-left corner of the hitbox to the exact given coordinates, without updating the offsets.
	// If you want to manipulate the positions of hitboxes relative to some other reference (e.g. changing the distance of a RelativeHitbox from its parent), you should use setOffsetPos instead
	Hitbox& Hitbox::move(const float x, const float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	// Resize the ui, without updating the offsets
	Hitbox& Hitbox::resize(const float x, const float y)
	{
		this->w = x;
		this->h = y;
		return *this;
	}

	// Set the x/y position, then update the offsets based on that new position
	Hitbox& Hitbox::setExactPos(const float x, const float y) {
		this->x = x;
		this->y = y;
		refreshOffsetPosX();
		refreshOffsetPosY();
		return *this;
	}

	// Set the x/y size, then update the offsets based on that new size
	Hitbox& Hitbox::setExactSize(const float x, const float y){
		this->w = x;
		this->h = y;
		refreshOffsetSizeX();
		refreshOffsetSizeY();
		return *this;
	}

	// Set the x position, then update the offsets based on that new position
	Hitbox& Hitbox::setExactPosX(const float x){
		this->x = x;
		refreshOffsetPosX();
		return *this;
	}

	// Set the y position, then update the offsets based on that new position
	Hitbox& Hitbox::setExactPosY(const float y){
		this->y = y;
		refreshOffsetPosY();
		return *this;
	}

	// Set the x size, then update the offsets based on that new size
	Hitbox& Hitbox::setExactSizeX(const float x) {
		this->w = x;
		refreshOffsetSizeX();
		return *this;
	}

	// Set the y size, then update the offsets based on that new size
	Hitbox& Hitbox::setExactSizeY(const float y){
		this->h = y;
		refreshOffsetSizeY();
		return *this;
	}

	// Change the x/y position offset ratio relative to some reference, then update the position
	Hitbox& Hitbox::setOffsetPos(const float x, const float y)
	{
		offsetPosX = x;
		offsetPosY = y;
		refreshExactPosX();
		refreshExactPosY();
		return *this;
	}

	// Change the width/height offset ratio relative to some reference, then update the size
	Hitbox& Hitbox::setOffsetSize(const float x, const float y)
	{
		offsetSizeX = x;
		offsetSizeY = y;
		refreshExactSizeX();
		refreshExactSizeY();
		return *this;
	}

	// Change the x offset ratio
	Hitbox& Hitbox::setOffsetPosX(const float x)
	{
		offsetPosX = x;
		refreshExactPosX();
		return *this;
	}

	// Change the y offset ratio
	Hitbox& Hitbox::setOffsetPosY(const float y)
	{
		offsetPosY = y;
		refreshExactPosY();
		return *this;
	}

	// Change the width offset ratio
	Hitbox& Hitbox::setOffsetSizeX(const float x)
	{
		offsetSizeX = x;
		refreshExactSizeX();
		return *this;
	}

	// Change the height offset ratio
	Hitbox& Hitbox::setOffsetSizeY(const float y)
	{
		offsetSizeY = y;
		refreshExactSizeY();
		return *this;
	}

	// Force all exact coordinates to refresh according to the offsets
	void Hitbox::refresh()
	{
		refreshExactPosX();
		refreshExactPosY();
		refreshExactSizeX();
		refreshExactSizeY();
	}

	// State update
	void Hitbox::update() {
		if (just) { just = false; }
		if (!hovered) {
			hovered = isMouseHovering();
			if (hovered) {
				just = true;
			}
		}
		else {
			hovered = isMouseHovering();
			if (!hovered) {
				just = true;
			}
		}
	}
}