export module fbc.uiBase;

import fbc.futil;
import fbc.hitbox;
import fbc.iOverlay;
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

		virtual void render() override;
		virtual void update() override;
		virtual void updateImpl();

		virtual void renderImpl() = 0;
	};

	void UIBase::render() {
		if (enabled) {
			renderImpl();
		}
	}

	void UIBase::update() {
		if (enabled) {
			updateImpl();
		}
	}

	void UIBase::updateImpl() {
		hb->update();
	}
}