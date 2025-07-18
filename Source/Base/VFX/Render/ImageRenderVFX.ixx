export module fab.ImageRenderVFX;

import fab.FUtil;
import fab.FWindow;
import fab.Hoverable;
import fab.UIImage;
import fab.UITransformVFX;
import fab.VFX;
import sdl.SDLBase; 
import fab.BatchRenderPass;
import sdl.SDLRunner;
import std;

namespace fab {
	export class ImageRenderVFX : public UITransformVFX {
	public:
		ImageRenderVFX(FWindow& window, uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f, float alphaEnd = 0): UITransformVFX(window, *image, duration, alphaEnd), image(move(image)) {}
		ImageRenderVFX(uptr<UIImage>&& image, float duration = DEFAULT_DURATION * 0.5f, float alphaEnd = 0) : UITransformVFX(image->win, *image, duration, alphaEnd), image(move(image)) {}

		uptr<UIImage> image;

		virtual void render(BatchRenderPass& rp) override;
	};

	void ImageRenderVFX::render(BatchRenderPass& rp) {
		image->render(rp);
	}
}