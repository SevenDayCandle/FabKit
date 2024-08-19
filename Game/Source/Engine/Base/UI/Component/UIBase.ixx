export module fbc.UIBase;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hitbox;
import fbc.RelativeHitbox;
import sdl;
import std;

namespace fbc {
	export class UIBase : public FWindow::Element {
	public:
		UIBase(FWindow& window, Hitbox* hb) : Element(window), hb(hb) {}
		UIBase(FWindow& window, uptr<Hitbox>&& hb) : Element(window), hb(std::move(hb)) {}
		virtual ~UIBase() override = default;

		uptr<Hitbox> hb;
		bool enabled = true;

		inline virtual float getBeginX() { return hb->x; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getBeginY() { return hb->y; } // The left-most end X coordinate of this object, may be smaller than hb if this has labels
		inline virtual float getEndX() { return hb->x + hb->w; } // The right-most end X coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual float getEndY() { return hb->y + hb->h; } // The bottom-most end Y coordinate of this object, may be larger than hb if this has subcomponents
		inline virtual bool isHovered() { return hb->isHovered(); }
		inline virtual void onSizeUpdated() {}
		inline virtual UIBase& setEnabled(const bool enabled) { return this->enabled = enabled, * this; }
		inline virtual UIBase& setHbExactPos(const float x, const float y) { return hb->setRealPos(x, y), *this; }
		inline virtual UIBase& setHbExactPosX(const float x) { return hb->setRealPosX(x), * this; }
		inline virtual UIBase& setHbExactPosY(const float y) { return hb->setRealPosY(y), * this; }
		inline virtual UIBase& setHbOffsetPos(const float x, const float y) { return hb->setOffPos(x, y), * this; }
		inline virtual UIBase& setHbOffsetPosX(const float x) { return hb->setOffPosX(x), * this; }
		inline virtual UIBase& setHbOffsetPosY(const float y) { return hb->setOffPosY(y), * this; }
		template <typename... Args> requires std::constructible_from<RelativeHitbox, Hitbox&, Args...> inline uptr<RelativeHitbox> relhb(Args... args) { return make_unique<RelativeHitbox>(&hb, std::forward<Args>(args)...); }
		template <typename T, typename... Args> requires std::constructible_from<T, FWindow&, Args...> uptr<T> inline create(Args... args) { return make_unique<T>(win, std::forward<Args>(args)...); }

		virtual UIBase& setHbExactSize(const float x, const float y);
		virtual UIBase& setHbExactSizeX(const float x);
		virtual UIBase& setHbExactSizeY(const float y);
		virtual UIBase& setHbOffsetSize(const float x, const float y);
		virtual UIBase& setHbOffsetSizeX(const float x);
		virtual UIBase& setHbOffsetSizeY(const float y);
		virtual void refreshDimensions() override;
		virtual void render(sdl::SDLBatchRenderPass& rp) final override;
		virtual void update() final override;
		virtual void updateImpl();

		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) = 0;
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

	// Inner logic of the update loop
	void UIBase::updateImpl() {
		hb->update();
	}
}