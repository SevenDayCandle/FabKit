export module fbc.hitbox;

import raylib;

export namespace fbc::hitbox {
	export class Hitbox : public raylib::Rectangle {
	public:
		Hitbox(): raylib::Rectangle() {}
		virtual ~Hitbox() {}

		inline bool isClicked() { return hovered && raylib::isMouseButtonDown(raylib::MouseButton::MOUSE_BUTTON_LEFT); };
		inline bool isClickedRight() { return hovered && raylib::isMouseButtonDown(raylib::MouseButton::MOUSE_BUTTON_RIGHT); };
		inline bool isHovered() const { return hovered; }
		inline bool justClicked() { return hovered && raylib::isMouseButtonPressed(raylib::MouseButton::MOUSE_BUTTON_LEFT); };
		inline bool justClickedRight() { return hovered && raylib::isMouseButtonPressed(raylib::MouseButton::MOUSE_BUTTON_RIGHT); };
		inline bool justHovered() const { return hovered && just; }
		inline float cX() { return (x + width) / 2; }
		inline float cY() { return (y + height) / 2; }
		inline Hitbox& moveCenter(const float x, const float y) { return move(x - (width / 2), y - (height / 2)); }
		virtual Hitbox& move(const float x, const float y);
		virtual Hitbox& resize(const float x, const float y);
		virtual void render();
		virtual void update();
	protected:
		bool just = false;
		bool hovered = false;
		virtual bool isMouseInHoverRange();
	};

	// Return true if the mouse is within the rectangle
	bool Hitbox::isMouseInHoverRange() {
		int mx = raylib::getMouseX();
		int my = raylib::getMouseY();
		return mx > x && my > y && mx < x + width && my < y + height;
	}

	// Move the bottom-left corner of the hitbox
	Hitbox& Hitbox::move(const float x, const float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	// Resize the hitbox
	Hitbox& Hitbox::resize(const float x, const float y)
	{
		this->width = x;
		this->height = y;
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