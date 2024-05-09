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
		virtual ~UIBase() {}

		uptr<Hitbox> hb;
		bool enabled = true;

		inline virtual bool isHovered() { return hb->isHovered(); }
		inline virtual void refreshSize() { hb->refresh(); } // Force updating of the hb dimensions to match their offsets. Invoked when the screen size is changed

		virtual void render() override;
		virtual void update() override;
		virtual void updateImpl();

		virtual void renderImpl() = 0;
	};

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