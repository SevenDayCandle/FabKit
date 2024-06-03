export module fbc.UIBase;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import std;

export namespace fbc {
	export class UIBase : public IOverlay {
	public:
		UIBase(Hitbox* hb) : hb(hb) {}
		UIBase(uptr<Hitbox>&& hb) : hb(std::move(hb)) {}
		virtual ~UIBase() override {}

		uptr<Hitbox> hb;
		bool enabled = true;

		inline virtual float getBeginX() { return hb->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return hb->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return hb->x + hb->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return hb->y + hb->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual bool isHovered() { return hb->isHovered(); }
		inline virtual void onSizeUpdated() {}

		UIBase& setHbExactSize(const float x, const float y);
		UIBase& setHbExactSizeX(const float x);
		UIBase& setHbExactSizeY(const float y);;
		UIBase& setHbOffsetSize(const float x, const float y);
		UIBase& setHbOffsetSizeX(const float x);
		UIBase& setHbOffsetSizeY(const float y);
		 
		virtual void refreshHb() override;
		virtual void render() override;
		virtual void update() override;
		virtual void updateImpl();

		virtual void renderImpl() = 0;
	};

	// Wrapper around setExactSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSize(const float x, const float y)
	{
		hb->setExactSize(x, y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setExactSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSizeX(const float x)
	{
		hb->setExactSizeX(x);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setExactSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSizeY(const float y)
	{
		hb->setExactSizeY(y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffsetSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSize(const float x, const float y)
	{
		hb->setOffsetSize(x, y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffsetSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSizeX(const float x)
	{
		hb->setOffsetSizeX(x);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffsetSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSizeY(const float y)
	{
		hb->setOffsetSizeY(y);
		onSizeUpdated();
		return *this;
	}

	// Force updating of the hb dimensions to match their offsets. Invoked when the screen size is changed
	void UIBase::refreshHb()
	{
		hb->refresh();
		onSizeUpdated();
	}

	// If enabled, render the component for a single frame
	void UIBase::render() {
		if (enabled) {
			renderImpl();
		}
	}

	// If enabled, update the component for a single frame
	void UIBase::update() {
		if (enabled) {
			updateImpl();
		}
	}

	// Inner logic of the update loop
	void UIBase::updateImpl() {
		hb->update();
	}
}