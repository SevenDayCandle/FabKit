export module fbc.DraggableHitbox;

import fbc.FUtil;
import fbc.ScaleHitbox;
import sdl;
import std;

export namespace fbc {
	export class DraggableHitbox : public ScaleHitbox {
	public:
		DraggableHitbox() : ScaleHitbox(0, 0, 0, 0) {}
		DraggableHitbox(float offsetWidth, float offsetHeight) : ScaleHitbox(0, 0, offsetWidth, offsetHeight) {}
		DraggableHitbox(float offsetX, float offsetY, float offsetWidth, float offsetHeight) : ScaleHitbox(offsetX, offsetY, offsetWidth, offsetHeight) {}
		~DraggableHitbox() override {}
	};
}