export module fbc.UIBase;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.Hoverable;
import fbc.RelativeHitbox;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLProps; 
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIBase : public Hoverable {
	public:
		UIBase(FWindow& window, uptr<Hitbox>&& hb) : Hoverable(window), hb(move(hb)) {}
		UIBase(UIBase&& other) noexcept = default;
		virtual ~UIBase() override = default;

		uptr<Hitbox> hb;
		bool enabled = true;

		inline Hitbox* getHb() final override { return hb.get(); }
		inline virtual bool isHovered() { return hb->isHovered(); }
		inline virtual float getBeginX() { return hb->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return hb->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return hb->x + hb->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return hb->y + hb->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual UIBase& setEnabled(const bool enabled) { return this->enabled = enabled, *this; }
		inline virtual UIBase& setHbExactPos(const float x, const float y) { return hb->setRealPos(x, y), * this; }
		inline virtual UIBase& setHbExactPosX(const float x) { return hb->setRealPosX(x), * this; }
		inline virtual UIBase& setHbExactPosY(const float y) { return hb->setRealPosY(y), * this; }
		inline virtual UIBase& setHbOffsetPos(const float x, const float y) { return hb->setOffPos(x, y), * this; }
		inline virtual UIBase& setHbOffsetPosX(const float x) { return hb->setOffPosX(x), * this; }
		inline virtual UIBase& setHbOffsetPosY(const float y) { return hb->setOffPosY(y), * this; }
		inline virtual void onSizeUpdated() {}
		inline virtual void updateImpl() override { hb->update(); }
		template <typename... Args> requires std::constructible_from<RelativeHitbox, FWindow&, Hitbox&, Args&&...> inline uptr<RelativeHitbox> relhb(Args&&... args) { return make_unique<RelativeHitbox>(win, *hb, forward<Args>(args)...); } // Generate a relative hitbox based on this component's hitbox

		virtual UIBase& setHbExactSize(const float x, const float y);
		virtual UIBase& setHbExactSizeX(const float x);
		virtual UIBase& setHbExactSizeY(const float y);
		virtual UIBase& setHbOffsetSize(const float x, const float y);
		virtual UIBase& setHbOffsetSizeX(const float x);
		virtual UIBase& setHbOffsetSizeY(const float y);
		virtual void refreshDimensions() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) final override;
		virtual void update() final override;
	};

	// Wrapper around setRealSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSize(const float x, const float y)
	{
		hb->setRealSize(x, y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setRealSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSizeX(const float x)
	{
		hb->setRealSizeX(x);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setRealSize that invokes any size update callbacks
	UIBase& UIBase::setHbExactSizeY(const float y)
	{
		hb->setRealSizeY(y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSize(const float x, const float y)
	{
		hb->setOffSize(x, y);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSizeX(const float x)
	{
		hb->setOffSizeX(x);
		onSizeUpdated();
		return *this;
	}

	// Wrapper around setOffSize that invokes any size update callbacks
	UIBase& UIBase::setHbOffsetSizeY(const float y)
	{
		hb->setOffSizeY(y);
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
	void UIBase::render(sdl::SDLBatchRenderPass& rp) {
		if (enabled) {
			renderImpl(rp);
		}
	}

	// If enabled, update the component for a single frame
	void UIBase::update() {
		if (enabled) {
			updateImpl();
		}
	}
}