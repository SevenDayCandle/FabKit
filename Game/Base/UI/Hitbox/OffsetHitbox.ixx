export module fbc.offsetHitbox;

import fbc;
import fbc.hitbox;

export namespace fbc::hitbox {
	export class OffsetHitbox : public Hitbox {
	public:
		OffsetHitbox() {}
		OffsetHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight) : offsetX(offsetX), offsetY(offsetY), offsetWidth(offsetWidth), offsetHeight(offsetHeight) {}
		~OffsetHitbox() override {}

		inline float getOffsetX() { return offsetX; }
		inline float getOffsetY() { return offsetY; }
	protected:
		float offsetX;
		float offsetY;
		float offsetWidth;
		float offsetHeight;
		OffsetHitbox& setOffsetPos(const float x, const float y);
		OffsetHitbox& setOffsetSize(const float x, const float y);
		OffsetHitbox& setOffsetX(const float x);
		OffsetHitbox& setOffsetY(const float y);
		OffsetHitbox& setOffsetWidth(const float x);
		OffsetHitbox& setOffsetHeight(const float y);
		virtual void refreshPosition() = 0;
		virtual void refreshSize() = 0;
	};

	// Change the x/y offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetPos(const float x, const float y)
	{
		offsetX = x;
		offsetY = y;
		refreshPosition();
		return *this;
	}

	// Change the width/height offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetSize(const float x, const float y)
	{
		offsetWidth = x;
		offsetHeight = y;
		refreshSize();
		return *this;
	}

	// Change the x offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetX(const float x)
	{
		offsetX = x;
		refreshPosition();
		return *this;
	}

	// Change the y offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetY(const float y)
	{
		offsetY = y;
		refreshPosition();
		return *this;
	}

	// Change the width offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetWidth(const float x)
	{
		offsetWidth = x;
		refreshSize();
		return *this;
	}

	// Change the height offset ratio
	OffsetHitbox& OffsetHitbox::setOffsetHeight(const float y)
	{
		offsetHeight = y;
		refreshSize();
		return *this;
	}
}