export module fbc.HitboxMoveVFX;

import fbc.FUtil;
import fbc.Hitbox;
import fbc.VFX;

namespace fbc {
	export class HitboxMoveVFX : public VFX {
	public:
		HitboxMoveVFX(Hitbox* hb, float duration = DEFAULT_DURATION): VFX() {}
		virtual ~HitboxMoveVFX() = default;

		float targOffsetX;
		float targOffsetY;
	};
}