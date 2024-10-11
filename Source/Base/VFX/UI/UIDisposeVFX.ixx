export module fab.UIDisposeVFX;

import fab.FUtil;
import fab.FWindow;
import fab.Hoverable;
import fab.UIImage;
import fab.UITransformVFX;
import fab.VFX;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class UIDisposeVFX : public UITransformVFX {
	public:
		UIDisposeVFX(FWindow& window, uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f): UITransformVFX(window, *image, duration, 0), image(move(image)) {}

		uptr<UIImage> image;
	};
}