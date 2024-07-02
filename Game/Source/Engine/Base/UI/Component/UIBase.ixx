export module fbc.UIBase;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.IOverlay;
import std;

namespace fbc {
	export class UIBase : public IOverlay {
	public:
		UIBase(Hitbox* hb) : hb(hb) {}
		UIBase(uptr<Hitbox>&& hb) : hb(std::move(hb)) {}
		virtual ~UIBase() override = default;

		uptr<Hitbox> hb;
		bool enabled = true;

		inline virtual float getBeginX() { return hb->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return hb->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return hb->x + hb->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return hb->y + hb->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual bool isHovered() { return hb->isHovered(); }
		inline virtual void onSizeUpdated() {}
		inline virtual UIBase& addVFX(uptr<IOverlay>&& vfx) { return *this; }
		inline virtual UIBase& setHbExactPos(const float x, const float y) { return hb->setExactPos(x, y), *this; }
		inline virtual UIBase& setHbExactPosX(const float x) { return hb->setExactPosX(x), * this; }
		inline virtual UIBase& setHbExactPosY(const float y) { return hb->setExactPosY(y), * this; }
		inline virtual UIBase& setHbOffsetPos(const float x, const float y) { return hb->setOffsetPos(x, y), * this; }
		inline virtual UIBase& setHbOffsetPosX(const float x) { return hb->setOffsetPosX(x), * this; }
		inline virtual UIBase& setHbOffsetPosY(const float y) { return hb->setOffsetPosY(y), * this; }

		virtual UIBase& setHbExactSize(const float x, const float y);
		virtual UIBase& setHbExactSizeX(const float x);
		virtual UIBase& setHbExactSizeY(const float y);
		virtual UIBase& setHbOffsetSize(const float x, const float y);
		virtual UIBase& setHbOffsetSizeX(const float x);
		virtual UIBase& setHbOffsetSizeY(const float y);
		 
		virtual void refreshDimensions() override;
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

	// When the screen size is changed, text and hitboxes must be resized
	void UIBase::refreshDimensions()
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