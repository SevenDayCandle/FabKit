export module fab.UIImage;

import fab.FUtil;
import fab.FWindow;
import fab.Hitbox;
import fab.IDrawable;
import fab.Tooltip;
import fab.UIBase;
import sdl.SDLBase; 
import sdl.SDLBatchRenderPass; 
import sdl.SDLRunner;

namespace fab {
	export class UIImage : public UIBase {
	public:
		UIImage(FWindow& window, uptr<Hitbox>&& hb, IDrawable& image) : UIBase(window, move(hb)), image(image) {}
		UIImage(UIImage&& other) noexcept = default;
		~UIImage() override {}

		sdl::Color color = sdl::COLOR_STANDARD;
		float rotation = 0;
		float scaleX = 1;
		float scaleY = 1;
		IDrawable& image;

		inline virtual UIImage& setColor(sdl::Color color) { return this->color = color, *this; }
		inline virtual UIImage& setImage(IDrawable& image) { return this->image = image, *this;}
		inline virtual UIImage& setRotation(const float rotation) { return this->rotation = rotation, *this; }
		inline virtual UIImage& setRotationDeg(const float rotation) { return this->rotation = sdl::rads(rotation), *this; }
		inline virtual UIImage& setScaleX(const float scaleX) { return this->scaleX = scaleX, *this; }
		inline virtual UIImage& setScaleY(const float scaleY) { return this->scaleY = scaleY, *this; }
		virtual void renderImpl(sdl::SDLBatchRenderPass& rp) override;
	};

	void UIImage::renderImpl(sdl::SDLBatchRenderPass& rp) {
		image.draw(rp, *hb.get(), win.getW(), win.getH(), scaleX, scaleY, rotation, &color);
	}
}