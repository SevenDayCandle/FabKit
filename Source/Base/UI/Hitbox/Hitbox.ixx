export module fab.Hitbox;

import fab.FUtil;
import fab.FWindow;
import sdl.SDLBase;
import sdl.SDLRunner;

namespace fab {
	export class Hitbox : public sdl::RectF {
	public:
		Hitbox(FWindow& window, float offsetX, float offsetY, float offsetWidth, float offsetHeight) : sdl::RectF(0, 0, 0, 0), win(window), offPosX(offsetX), offPosY(offsetY), offSizeX(offsetWidth), offSizeY(offsetHeight) {}
		virtual ~Hitbox() = default;

		FWindow& win;

		inline bool isClicked() const { return hovered && sdl::runner::mouseIsLeftClicked(); };
		inline bool isClickedRight() const { return hovered && sdl::runner::mouseIsRightClicked(); };
		inline bool isHovered() const { return hovered; }
		inline bool isJust() const { return just; }
		inline bool justClicked() const { return hovered && sdl::runner::mouseIsLeftJustClicked(); };
		inline bool justClickedRight() const { return hovered && sdl::runner::mouseIsRightJustClicked(); };
		inline bool justHovered() const { return hovered && just; }
		inline bool justUnhovered() const { return !hovered && just; }
		inline float cX() const { return x + (w / 2); }
		inline float cY() const { return y + (h / 2); }
		inline float getOffPosX() const { return offPosX; } // Get the offset x position. How this translates into an actual screen coordinate depends on the hitbox
		inline float getOffPosX(float mult) const { return offPosX * mult; }
		inline float getOffPosY() const { return offPosY; } // Get the offset y position. How this translates into an actual screen coordinate depends on the hitbox
		inline float getOffPosY(float mult) const { return offPosY * mult; }
		inline float getOffSizeX() const { return offSizeX; } // Get the offset width. How this translates into an actual width depends on the hitbox
		inline float getOffSizeX(float mult) const { return offSizeX * mult; }
		inline float getOffSizeY() const { return offSizeY; } // Get the offset height. How this translates into an actual height depends on the hitbox
		inline float getOffSizeY(float mult) const { return offSizeY * mult; }
		inline float getScaledOffPosX(float mult) const { return getScaledOffPosX() * mult; }
		inline float getScaledOffPosY(float mult) const { return getScaledOffPosY() * mult; }
		inline float getScaledOffSizeX(float mult) const { return getScaledOffSizeX() * mult; }
		inline float getScaledOffSizeY(float mult) const { return getScaledOffSizeY() * mult; }
		inline virtual float getScaledOffPosX() const { return offPosX; } // Get the offset x position as it would look for scaled hitboxes. This is identical to getOffPosX for relative/scale hitboxes and is multiplied by the screen size for screenpos/screensize hitboxes 
		inline virtual float getScaledOffPosY() const { return offPosY; } // Get the offset y position as it would look for scaled hitboxes. This is identical to getOffPosY for relative/scale hitboxes and is multiplied by the screen size for screenpos/screensize hitboxes 
		inline virtual float getScaledOffSizeX() const { return offSizeX; } // Get the offset x scale as it would look for scaled hitboxes. This is identical to getOffSizeX for relative/scale/screenpos hitboxes and is multiplied by the screen size for screensize hitboxes 
		inline virtual float getScaledOffSizeY() const { return offSizeY; } // Get the offset y scale as it would look for scaled hitboxes. This is identical to getOffSizeY for relative/scale/screenpos hitboxes and is multiplied by the screen size for screensize hitboxes 

		Hitbox& setOffPos(const float x, const float y);
		Hitbox& setOffPosX(const float x);
		Hitbox& setOffPosY(const float y);
		Hitbox& setOffSize(const float x, const float y);
		Hitbox& setOffSizeX(const float x);
		Hitbox& setOffSizeY(const float y);
		Hitbox& setRealPos(const float x, const float y);
		Hitbox& setRealPosX(const float x);
		Hitbox& setRealPosY(const float y);
		Hitbox& setRealSize(const float x, const float y);
		Hitbox& setRealSizeX(const float x);
		Hitbox& setRealSizeY(const float y);
		void refresh();
		virtual void update();

		virtual float toOffPosX(float x) const = 0; // Get the offset position x for this hitbox that corresponds with the real coordinate x
		virtual float toOffPosY(float y) const = 0; // Get the offset position y for this hitbox that corresponds with the real coordinate x
		virtual float toRealPosX(float offX) const = 0; // Get the real position x for this hitbox that corresponds with the offset x
		virtual float toRealPosY(float offY) const = 0; // Get the real position y for this hitbox that corresponds with the offset y
	protected:
		bool hovered = false;
		bool just = false;
		float offPosX = 0;
		float offPosY = 0;
		float offSizeX = 0;
		float offSizeY = 0;

		virtual bool isMouseHovering();

		virtual void refreshOffPosX() = 0;
		virtual void refreshOffPosY() = 0;
		virtual void refreshOffSizeX() = 0;
		virtual void refreshOffSizeY() = 0;
		virtual void refreshRealPosX() = 0;
		virtual void refreshRealPosY() = 0;
		virtual void refreshRealSizeX() = 0;
		virtual void refreshRealSizeY() = 0;
	};

	// Return true if the mouse is within the rectangle. Note that the Y coordinates goes from top to bottom, with 0,0 being the top-left corner of the screen
	bool Hitbox::isMouseHovering() {
		return sdl::runner::mouseIsHovering(*this);
	}

	// Change the x/y position offset ratio relative to some reference, then update the position
	Hitbox& Hitbox::setOffPos(const float x, const float y)
	{
		offPosX = x;
		offPosY = y;
		refreshRealPosX();
		refreshRealPosY();
		return *this;
	}

	// Change the width/height offset ratio relative to some reference, then update the size
	Hitbox& Hitbox::setOffSize(const float x, const float y)
	{
		offSizeX = x;
		offSizeY = y;
		refreshRealSizeX();
		refreshRealSizeY();
		return *this;
	}

	// Change the x offset ratio
	Hitbox& Hitbox::setOffPosX(const float x)
	{
		offPosX = x;
		refreshRealPosX();
		return *this;
	}

	// Change the y offset ratio
	Hitbox& Hitbox::setOffPosY(const float y)
	{
		offPosY = y;
		refreshRealPosY();
		return *this;
	}

	// Change the width offset ratio
	Hitbox& Hitbox::setOffSizeX(const float x)
	{
		offSizeX = x;
		refreshRealSizeX();
		return *this;
	}

	// Change the height offset ratio
	Hitbox& Hitbox::setOffSizeY(const float y)
	{
		offSizeY = y;
		refreshRealSizeY();
		return *this;
	}

	// Set the x/y position, then update the offsets based on that new position
	Hitbox& Hitbox::setRealPos(const float x, const float y) {
		this->x = x;
		this->y = y;
		refreshOffPosX();
		refreshOffPosY();
		return *this;
	}

	// Set the x position, then update the offsets based on that new position
	Hitbox& Hitbox::setRealPosX(const float x) {
		this->x = x;
		refreshOffPosX();
		return *this;
	}

	// Set the y position, then update the offsets based on that new position
	Hitbox& Hitbox::setRealPosY(const float y) {
		this->y = y;
		refreshOffPosY();
		return *this;
	}

	// Set the x/y size, then update the offsets based on that new size
	Hitbox& Hitbox::setRealSize(const float x, const float y) {
		this->w = x;
		this->h = y;
		refreshOffSizeX();
		refreshOffSizeY();
		return *this;
	}

	// Set the x size, then update the offsets based on that new size
	Hitbox& Hitbox::setRealSizeX(const float x) {
		this->w = x;
		refreshOffSizeX();
		return *this;
	}

	// Set the y size, then update the offsets based on that new size
	Hitbox& Hitbox::setRealSizeY(const float y) {
		this->h = y;
		refreshOffSizeY();
		return *this;
	}

	// Force all exact coordinates to refresh according to the offsets
	void Hitbox::refresh()
	{
		refreshRealPosX();
		refreshRealPosY();
		refreshRealSizeX();
		refreshRealSizeY();
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