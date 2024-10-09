export module fbc.UIDisposeVFX;

import fbc.FUtil;
import fbc.FWindow;
import fbc.Hoverable;
import fbc.UIImage;
import fbc.UITransformVFX;
import fbc.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fbc {
	export class UIDisposeVFX : public UITransformVFX {
	public:
		UIDisposeVFX(FWindow& window, uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f): UITransformVFX(window, *image, duration, 0), image(move(image)) {}

		uptr<UIImage> image;
	};
}